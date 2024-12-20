# transfer-files
This program simulates a simple file transfer protocol for a file repository.

First, this program is written on C language programming (and compile on a Linux environment), so the user needs to install the C/C++ environment before to run this program. 

Second, the user need to go to the server.c file and look for 'char filename_[256]' line. Once it was found, please copy the path of the file Repository within the quotation marks and add '/Repository/'. The code expects a file_path/Repository/ format, so the program would not read the files that are on the Repository directory if this step is skipped.

Then, the user needs to run the following commands on the Terminal prompt:
Run the server.c FIRST in one Terminal window with:
1. gcc server.c -o server
2. ./server

Run the client.c in another Terminal window with:
1. gcc client.c -o client
2. ./client

Important:
Two different windows need to be open to keep track of the changes on this program.

Inputs:

This programs accept three types of inputs. 
* 'terminate' kills both processes on the two different windows.
* 'exit' kills the client process. Then, the user needs to kill manually the server.c window.
* 'filename' which can be any file name. The Repository contains .txt files and it was initiliazed with three files. User can type those file names and type any other file name that is not on the directory. Of course, by typing a name that is not on the Repository directory, the program will prompt the 'file not found' message.

Finally, here is an outline of the key responsabilities, features, and challenges experimented on this project:

Key Responsibilities:

* Socket Creation and Binding: Implemented server-side socket creation and binding to an IP address and port, allowing the server to listen for incoming connections.
* Connection Handling: Handled multiple client connections using the accept() system call and managed message exchange over sockets.
* File Request Processing: Parsed client requests for specific files, validated the request, and responded with either file details or an error message if the file was missing.
* Error Handling: Added robust error handling to ensure the server can handle connection issues, file access problems, and communication failures gracefully.
* Message Validation: Implemented string comparison logic to validate commands such as "terminate" and "exit", ensuring the server correctly responds to client shutdown requests.
* File I/O: Managed file access, including checking for file existence, calculating file size, and sending file details back to the client.

Key Features:
* Dynamic Client Interaction: The server continuously listens for and accepts connections, allowing for real-time interactions with clients.
* Request Validation: Validated client messages to ensure only valid requests for file information are processed.
* File Size Calculation: Implemented logic to calculate and send the number of bytes in a requested file.
* Client-Server Communication: Sent and received messages over a network using TCP, ensuring reliable communication between server and client.

Challenges Overcome:

* Handled socket binding retries to ensure the server remains resilient to potential conflicts with the chosen port.
* Managed various network errors and client disconnects to ensure stable server operation.