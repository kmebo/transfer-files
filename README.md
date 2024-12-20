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