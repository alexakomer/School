#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>

using namespace std;

int hextoDec(string hexVal)
{
    int len = hexVal.size();
 
    int base = 1;
 
    int dec_val = 0;
 
    for (int i = len - 1; i >= 0; i--) 
    {
        if (hexVal[i] >= '0' && hexVal[i] <= '9') 
        {
            dec_val += (int(hexVal[i]) - 48) * base;
            base = base * 16;
        }

        else if (hexVal[i] >= 'a' && hexVal[i] <= 'f')
        {
            dec_val += (int(hexVal[i]) - 87) * base; 
            base = base * 16;
        }
    }
    return dec_val;
}

int main(int argc, char *argv[])
{   

    string url = "";
    string filename = "";

    if(argv[1]) // when url argument is provided, assign it
        url = argv[1]; // DO I NEED TO PARSE OUT THE ANCHOR (#)

    if (argv[2]) // when filename is provided, assign it
        filename = argv[2];

    bool keepGoing = true;
    while(keepGoing)
    {
        keepGoing = false; // will be reassigned true only in cases of redirection

        string host;
        string path = "/";

        // Handle parsing -------------------------------

        if(url.substr(0,7) == "http://") // account for cases with http
            url = url.substr(7);
        else if(url.substr(0,8) == "https://") // account for cases with https
            url = url.substr(8);

        size_t found = url.find_first_of('/'); // parse path based on presence of /
        if (found != std::string::npos)
        {
            host = url.substr(0, found);
            path += url.substr(found + 1);
        }
        else
            host = url;

        if (filename == "")
        {
            int pos = path.find_last_of('/');
            filename = path.substr(pos + 1); // default filename to path
        }

        if (filename == "" || filename == "/")
            filename = "index.html"; // default filename to index.html if no path is provided

        struct addrinfo sd, *res;

        // Creating channel --------------------------
        
        string port = "80";
        
        int sockfd;

        memset(&sd, 0, sizeof sd);
        sd.ai_family = AF_UNSPEC;
        sd.ai_socktype = SOCK_STREAM;
        int status;


        if ((status = getaddrinfo (host.c_str(), port.c_str(), &sd, &res)) != 0) 
        {
            cerr << "Addr info " << gai_strerror(status) << endl;
            exit(-1);
        }

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); // create socket
        if (sockfd < 0)
        {
            perror ("Socket unable to be created");    
            exit(-1);
        }

        if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) // connect
        {
            perror ("Connection failed");
            exit(-1);
        }

        freeaddrinfo(res);


        // Sending request --------------------------

        string request = "GET " + path + " HTTP/1.1\r\nHost: " + host + "\r\nConnection:close\r\n\r\n";

        send(sockfd, request.c_str(), strlen(request.c_str()), 0);

        // Receving response --------------------------

        char buffer[1000001]; // buffer of arbitrary fixed size is OK
        int i = 0 ;
        int nDataLength = 0;
        string website_HTML;

        while ((nDataLength = recv(sockfd, buffer, 1000000, 0)) > 0) // iterate while there is still data left in response
        {   
            int i = 0;
            buffer[1000000] = '/0'; // make sure buffer is ended by sentinel byte
            while (i < nDataLength) // bound checking
            {
                website_HTML += buffer[i];
                i++;
            }               
        }

        close(sockfd);

        // Parsing header -----------------------

        int headparse = website_HTML.find("\r\n\r\n"); // split at blank line
        string header = website_HTML.substr(0, headparse);
        string body = website_HTML.substr(headparse + 4);

        int response = stoi(header.substr(0, header.find("\n")).substr(header.find(' ') + 1, 3));

        // Writing to file ---------------------

        if (response == 200) // on success
        {
            if (header.find("transfer-encoding: chunked") != -1) // handle transfer encoding cases
            {
                int endpos = body.find("\r\n\r\n");

                string newBody = "";
                int chunkSize;

                int i = 0;
                while (i < endpos)
                {
                    string hexStr = "0x";
                    while(body[i] != '\n')
                    {
                        hexStr += body[i]; // read in hex string to understand how far to read
                        i++;
                    }
                    i++;
                    // if (hexStr == "0x0")
                    //     break;

                    chunkSize = hextoDec(hexStr);
                    string temp = body.substr(i, chunkSize);

                    newBody += temp; // append chunks to body
                    i += chunkSize + 2;
                }

                ofstream doc;
                doc.open(filename, ios::binary);
                doc << newBody;
                doc.close();
            }
            else
            {
                ofstream doc;
                doc.open(filename, ios::binary);
                doc << body;
                doc.close();
            }
        }

        else if(response == 301 || response == 302) // on redirections
        {
            int locIndex = header.find("location: ");
            int i = locIndex + 10;
            string loc = "";
            while (header[i] != '\r')
            {
                loc += header[i];
                i++;
            }

            keepGoing = true;

            url = loc;
        }
        else if(response >= 400)
        {
            perror("Error code above 400");
            exit(1);
        }

    }

    return 0;
}