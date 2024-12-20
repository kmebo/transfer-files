#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>

#define PORT 19992

void error(char *msg) {
    perror(msg);
    exit(1);
} // error
int validateInt(char *MyClientCommand, char *EndStr)
{
    while (*MyClientCommand != '\0' && *EndStr != '\0')
    {
        if (*MyClientCommand != *EndStr) {
            return 1; // Strings are different
        }
        MyClientCommand++; EndStr++;
    }
    // If both strings end at the same time, they are equal
    return 0;
}
int main() 
{
    int sockd, newsockd, aliceLen;
    struct sockaddr_in bob_addr3, alice_addr3;
    char buffer[256] = {0};
    FILE *file;
    char filename_[256] = "add_changes_here";// 'file_path/Repository/' format expected
    long count_bytes = 0;

    printf("Please, wait until the message, 'Server is now 'listening.' appears below.\n");
    int create_socket = 1;
    while (create_socket)
    {
        // Server creates a socket
        sockd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockd < 0) {
            // printf("ERROR on creating a socket, try again.\n");
        }
        else{
            // Server builds his address
            bzero((char *) &bob_addr3, sizeof(bob_addr3));
            bob_addr3.sin_family = AF_INET;
            bob_addr3.sin_addr.s_addr = INADDR_ANY;
            bob_addr3.sin_port = htons(PORT);

            int binding_cond = 1;
            int binding_tries = 0;//just for curiosity to know how much time does a binding needs.
            while(binding_cond)
            {
                // Server binds the socket to his address
                if (bind(sockd, (struct sockaddr *) &bob_addr3,
                        sizeof(bob_addr3)) < 0) {
                        // printf("ERROR on binding, try again. #%d\n", binding_tries);
                        if (binding_tries > 50000)
                        {
                            binding_cond = 0;
                            close(sockd);
                        }
                        binding_tries++;
                } // if
                else
                {
                    binding_cond = 0;
                    create_socket = 0;
                }
            }
        }
    }
    
    listen(sockd,5);
    printf("Thansks for being patient :)!\nServer is now 'listening.'\n");
    
    char new_string[256];
    while (1)
    { 
            // Server accepts a connection
            aliceLen = sizeof(alice_addr3);
            newsockd = accept(sockd, (struct sockaddr *) &alice_addr3, &aliceLen);
            if (newsockd < 0)  {
                printf("ERROR on accept");
            }

            // Receive data from client
            if (recv(newsockd, buffer, 256, 0) == -1) {
                perror("Receive failed");
                exit(EXIT_FAILURE);
            }
            printf("Message from client: %s\n", buffer);

            int x1 = validateInt(buffer, "terminate");
            int y = validateInt(buffer, "exit");
            
            if(x1 != 1)// It means that buffer equals to "exit"
            {
                    printf("Goodbye!\n");
                    //Free Memory
                    memset(new_string, 0, 256);
                    memset(buffer, 0, 256);

                    close(newsockd);
                    break;
            }
            else if(y != 1)// It means that buffer equals to "exit"
            {
                printf("This is an exit message. Bye!\n");
            }
            else
            {
                buffer[strcspn(buffer, "\n")] = 0; // Remove trailing newline

                strcat(new_string, "A client requested the file ");
                strcat(new_string, buffer);

                printf("filename_: %s\n", filename_);
                
                char tem_filename[128] = {0};
                strcat(tem_filename, filename_);
                strcat(tem_filename, buffer);
                printf("tem_filename: %s\n", tem_filename);
                // Open the file in read mode
                file = fopen(tem_filename, "r");
                memset(tem_filename, 0, 128);

                // Check if the file exists
                if (file == NULL) {
                    strcat(new_string, ".\nThat file is missing!\n");
                }else{
                    // Count the number of bytes in the file
                    fseek(file, 0, SEEK_END); // Move the file pointer to the end of the file
                    count_bytes = ftell(file); // Get the position of the file pointer, which is the number of bytes
                    char count_str [20]; 
                    sprintf(count_str, "%ld", count_bytes);// Convert long to string

                    strcat(new_string, ".\nSent ");
                    strcat(new_string, count_str);
                    strcat(new_string, " bytes\n");
                    
                    memset(count_str, 0, 20);
                }
                fclose(file);

                if (send(newsockd, new_string, strlen(new_string), 0) == -1) {
                    perror("Send failed");
                    exit(EXIT_FAILURE);
                }
                // Clear the new_string
                memset(new_string, 0, 256);

            } 
            // Clear the buffer
            memset(buffer, 0, 256);
            close(newsockd);
        // }
    }
    // Clear the buffer
    memset(buffer, 0, 256);
    close(sockd);

    return 0;
}//main