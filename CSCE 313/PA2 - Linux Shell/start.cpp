#include <stdio.h>
#include<iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <ctime>

using namespace std;

string trim(string input) 
{
    string trimmed_input;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] != ' ')
        {
            trimmed_input.push_back(input[i]);
            if(input[i+1] == ' ')
                trimmed_input.push_back(' ');
        }

    }
    if(trimmed_input[trimmed_input.size() - 1] == ' ')
        trimmed_input.erase(trimmed_input.size() - 1);

    return trimmed_input;
}

vector<string> splitString(string line, char separator = ' ')
{
    vector<string> separated_input;
    int c = 0;
    int num_quotes = 0; //= count_num_quotes(line);
    bool inside_quotes = false;
    int start = 0;

    for(auto i = 0; i < line.size(); i++)
    {

        if (separator == ' ' && (line[i] == '\'' || line[i] == '\"'))
        {
            ++num_quotes;
            string word;
            if (num_quotes %2 !=0)
            {
                inside_quotes = true;
                start = i+1;
            }
            else //quote finished
            {
                inside_quotes = false;
                for (int j = start; j < i; j++)
                    word.push_back(line[j]);
                separated_input.push_back(word);
            }
        }
        else if (inside_quotes == false)
        {
            if((line[i] == separator) || (i == (line.size()-1)))
            {
                string words ;
                if (i == line.size() - 1)
                {
                    for (int j = c; j < i + 1; j++)
                        words.push_back(line[j]);
                }
                else
                {
                    for (int j = c; j < i; j++)
                        words.push_back(line[j]);
                }
                separated_input.push_back(words);
                c = i + 1;
            }

        }
    }
    return separated_input;
}

char** vec_to_arr(vector<string>& parts)
{
	char** result = new char* [parts.size() +1];//adds one because of NULL
	for (int i = 0; i < parts.size(); i++)
	{
		result[i] = (char*) parts[i].c_str();
	}

	result [parts.size()] = NULL;
	return result;
}

int main ()
{
    vector <int> bgs; // a list of the background processes
    while (true)
    { // make terminal loop infiinitely until "exit" is entered

        char buf[1000];
        string current_dir = getcwd(buf,sizeof(buf));
        chdir("..");
        string previous_dir = getcwd(buf,sizeof(buf));
        chdir(current_dir.c_str());

        for (int i = 0; i < bgs.size(); i++)
        {
            if (waitpid(bgs[i], 0, WNOHANG) == bgs[i]) // only remove process when status has changed to ended
            {

                cout << "Process: " << bgs[i] << " ended." << endl;
                bgs.erase(bgs.begin() + i); // remove background process
                i--;
            }
        }

        // custom prompt
        time_t result = time(0);
        string timeNow = ctime(&result);
        timeNow = timeNow.substr(0, timeNow.size() - 1);
        cout << "alexa " << timeNow << "$ ";

        string inputline;
        getline (cin, inputline); // get a line from standard input

        if (inputline == string("exit"))
        { // make a way to exit
            cout << "Terminal exited" << endl;
            break;
        }

        bool bgExists = false;
		inputline = trim(inputline); // remove leading and trailing spaces
		if(inputline[inputline.size()-1] == '&')
		{
			bgExists = true;
			inputline = trim(inputline.substr(0,inputline.size()-1)); // remove ampersand from command
        }


        vector<string> tokens = splitString (inputline); // tokenize inputline to check if cd command works

        // handling cd

        bool cdCommand = false;

        if(trim(tokens[0]) == "cd")
        {
            cdCommand = true;
            current_dir = getcwd(buf, sizeof(buf));
            if (trim(tokens[1]) == "-") 
            {
                chdir(previous_dir.c_str());
                previous_dir = current_dir;
            }
            else
            {
                string dirname = trim(tokens[1]);
                string fullDir = current_dir + "/" + dirname;
                // cout << "this is the new folder: " << fullDir << endl;
                chdir(fullDir.c_str());
                previous_dir = current_dir;
            }
            continue;
        }

        if (!cdCommand)
        {
        
            int pid = fork ();
            if (pid == 0)
            { //child process

                // handling piping

                tokens = splitString (inputline); // tokenize inputline and check for "|"

                bool pipeExists = false;

                for (int i = 0; i < tokens.size(); i++)
                {
                    if (tokens[i] == "|")
                        pipeExists = true;
                }

                if (pipeExists) // handles piping
                {
                    vector<string> pipeTokens = splitString(inputline, '|');

                    for (int i = 0; i < pipeTokens.size(); i++) // trimming
                    {
                        pipeTokens[i] = trim(pipeTokens[i]);
                        // cout << pipeTokens[i] << endl;
                    }

                    for (int i = 0; i < pipeTokens.size() - 1; i++) // handles actual piping cases and forks
                    {
                        int fds[2];
                        pipe(fds);
                        int subPID = fork();
                        if (!subPID) // child of the child processes
                        {
                            vector<string> singleCommand = splitString(pipeTokens[i]);
                            char ** pipeArgs = vec_to_arr(singleCommand);

                            if (i < pipeTokens.size() - 1)
                            {
                                dup2(fds[1], 1);    
                            }
                            
            
                            // handling IO redirection in special piping cases

                            bool less = false;
                            bool greater = false;

                            for (int i = 0; i < singleCommand.size(); i++)
                            {
                                if (singleCommand[i] == "<")
                                    less = true;
                                if (singleCommand[i] == ">")
                                    greater = true;
                            }


                            int pos = pipeTokens[i].find('>'); // handle IO redirection
                            if (pos >= 0 && greater)
                            {
                                string command = trim(pipeTokens[i].substr(0, pos));
                                string filename = trim(pipeTokens[i].substr(pos + 1)); // everything after ">" becomes a file
                                pipeTokens[i] = command;
                                int fd = open(filename.c_str(), O_WRONLY|O_CREAT,S_IWUSR|S_IRUSR); // open file and redirect to it
                                dup2(fd,1);
                                close(fd);
                            }

                            pos = pipeTokens[i].find('<'); // handle other case of IO redirection
                            if (pos >= 0 && less)
                            {
                                string command = trim(pipeTokens[i].substr(0, pos));
                                string filename = trim(pipeTokens[i].substr(pos + 1)); // everything after "<" becomes a file
                                pipeTokens[i] = command;
                                int fd = open(filename.c_str(), O_RDONLY,S_IWUSR|S_IRUSR); // open file and redirect from it
                                dup2(fd,0);
                                close(fd);
                            }

                            if (greater || less)
                            {
                                singleCommand = splitString(pipeTokens[i]);
                                pipeArgs = vec_to_arr(singleCommand);
                            }
                            
                            execvp(pipeArgs[0], pipeArgs);
                        }
                        else // parent of the child processes
                        {
                            if (i == pipeTokens.size() - 1)
                            {
                                waitpid(subPID, 0, 0);    
                            }

                            dup2(fds[0], 0);
                            close(fds[1]);

                            inputline = pipeTokens[i + 1];

                        }

                    }

                }

                tokens = splitString (inputline); // tokenize inputline again and check for "<" or ">"

                // handling IO redirection

                bool less = false;
                bool greater = false;

                for (int i = 0; i < tokens.size(); i++)
                {
                    if (tokens[i] == "<")
                        less = true;
                    if (tokens[i] == ">")
                        greater = true;
                }

                // the above booleans confirm that the "<" or ">" are not within quotes

                int pos = inputline.find('>'); // handle IO redirection
                if (pos >= 0 && greater)
                {
                    string command = trim(inputline.substr(0, pos));
                    string filename = trim(inputline.substr(pos + 1)); // everything after ">" becomes a file
                    inputline = command;
                    int fd = open(filename.c_str(), O_WRONLY|O_CREAT,S_IWUSR|S_IRUSR); // open file and redirect to it
                    dup2(fd,1);
                    close(fd);
                }

                pos =inputline.find('<'); // handle other case of IO redirection
                if (pos >= 0 && less)
                {
                    string command = trim(inputline.substr(0, pos));
                    string filename = trim(inputline.substr(pos + 1)); // everything after "<" becomes a file
                    inputline = command;
                    int fd = open(filename.c_str(), O_RDONLY,S_IWUSR|S_IRUSR); // open file and redirect from it
                    dup2(fd,0);
                    close(fd);
                }

                
                tokens = splitString (inputline); // split again with new inputline to feed into execvp command
                char** args = vec_to_arr(tokens);

                execvp (args [0], args);
            }
            else
            {
                if (!bgExists)
                    waitpid (pid, 0, 0); // wait for the child process
                else
                {
                    bgs.push_back(pid); // if it is a background process, add it to the vector of background processes
                }
            }
        }
    }
}