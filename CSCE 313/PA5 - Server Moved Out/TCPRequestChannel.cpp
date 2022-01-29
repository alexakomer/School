#include <string>
#include "common.h"
#include "TCPRequestChannel.h"
using namespace std;

// Constructor
TCPRequestChannel::TCPRequestChannel(const string host, const string port)
{

    if(host == "") // server
    {
        struct addrinfo sd, *serv;
        struct sockaddr_storage other_address; 
        socklen_t s_size;
        char s[INET6_ADDRSTRLEN];
        int rv;

        memset(&sd, 0, sizeof sd);
        sd.ai_family = AF_UNSPEC;
        sd.ai_socktype = SOCK_STREAM;
        sd.ai_flags = AI_PASSIVE; 

        if ((rv = getaddrinfo(NULL, port.c_str(), &sd, &serv)) != 0) 
        {
            cerr  << "Addr error: " << gai_strerror(rv) << endl;
            exit(-1);
        }

        if ((sockfd = socket(serv->ai_family, serv->ai_socktype, serv->ai_protocol)) == -1) 
        {
            perror("Server Socket ");
            exit(-1); 
        }

        if (bind(sockfd, serv->ai_addr, serv->ai_addrlen) == -1) 
        {
            close(sockfd);
            perror("server bind");
            exit(-1);
        }

        freeaddrinfo(serv); 
        if (listen(sockfd, 20) == -1) 
        {
            perror("listen");
            exit(1);
        }

        cout << "The server is ready for port num " << port <<endl;
    }
    else //client 
    {
        struct addrinfo sd, *res;

        memset(&sd, 0, sizeof sd);
        sd.ai_family = AF_UNSPEC;
        sd.ai_socktype = SOCK_STREAM;
        int status;

        if ((status = getaddrinfo (host.c_str(), port.c_str(), &sd, &res)) != 0) 
        {
            cerr << "Addr info " << gai_strerror(status) << endl;
            exit(-1);
        }

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
        {
            perror ("Socket unable to be created");    
            exit(-1);
        }

        if (connect(sockfd, res->ai_addr, res->ai_addrlen)<0)
        {
            perror ("Connection failed");
            exit(-1);
        }

        freeaddrinfo(res);
    }
}

// Alternate constructor
TCPRequestChannel::TCPRequestChannel (int fd)
{
    sockfd = fd;
}

// Destructor
TCPRequestChannel::~TCPRequestChannel()
{
    close(sockfd);
}

// Read messages from TCP
int TCPRequestChannel::cread(void* msgbuf, int buflen)
{
    return recv(sockfd, msgbuf, buflen, 0);
}

// Write messages through TCP
int TCPRequestChannel::cwrite(void* msgbuf , int msglen)
{
    return send(sockfd, msgbuf, msglen, 0);
}

// Return the socket file descriptor
int TCPRequestChannel::getfd()
{
    return sockfd;
}
