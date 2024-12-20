
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <errno.h>

#define MAX_HOSTNAME_LEN 256
#define PORT 19992

void error(char *msg)
{
    perror(msg);
    exit(0);
}
int get_hostname(char *hostname) {
    if (gethostname(hostname, MAX_HOSTNAME_LEN) == 0) {
        // Hostname retrieval successful
        return 0;
    } else {
        // Hostname retrieval failed
        fprintf(stderr, "Error getting hostname: %s\n", strerror(errno));
        return errno;
    }
}
int validateInt(char *MyClientCommand, char *EndStr){
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
    int sockd, n;
    struct hostent *bob_host3;
    struct sockaddr_in bob_address3;
    char hostname[MAX_HOSTNAME_LEN];

    char MyClientCommand[256]; 
    char EndStr[] = "terminate";
    char buffer[256] = {0};

    int x = 1;
    int y;
    while (x != 0)
    {
        // Client creates a socket
        sockd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockd < 0) {
            error("ERROR opening socket");
        }

        // Retriving hostname
        if (get_hostname(hostname) != 0) {
            fprintf(stderr, "Failed to get hostname.\n");
        } 

        // Alice builds Bob's host address
        bob_host3 = gethostbyname(hostname);
        if (bob_host3 == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        } //if
    
        // Client does some withcraft
        bzero((char *) &bob_address3, sizeof(bob_address3));
        bob_address3.sin_family = AF_INET;
        bcopy((char *)bob_host3->h_addr, 
            (char *)&bob_address3.sin_addr.s_addr,
            bob_host3->h_length);
        bob_address3.sin_port = htons(PORT);
        
        // Alice connects to Bob
        if (connect(sockd,(struct sockaddr *)&bob_address3,sizeof(bob_address3)) < 0) {
            printf("Error connecting! Try again.\n");
        } // if
   
        // Prompt the user to enter a command
        printf("Enter terminate, exit, or filename: ");
        // Read the input string from the command line
        fgets(MyClientCommand, sizeof(MyClientCommand), stdin);

        x = validateInt(MyClientCommand, EndStr);
        y = validateInt(MyClientCommand, "exit");

        // Send data to server
        if (send(sockd, MyClientCommand, strlen(MyClientCommand), 0) == -1) {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        if(x != 1){ break;}
        else if(y != 1){break;}
        else
        {
            // Receive response from server
            if (recv(sockd, buffer, 256, 0) == -1) {
                perror("Receive failed");
                exit(EXIT_FAILURE);
            }
            printf("%s\n", buffer);

            // Clear the buffer
            memset(buffer, 0, 256);
            x = 1;
        }
        // Clear MyClientCommand
        memset(MyClientCommand, 0, 256);
    }
    // Clear MyClientCommand
    memset(MyClientCommand, 0, 256);
    memset(buffer, 0, 256);
    // Close the client socket
    close(sockd);
    
    return 0;
}
