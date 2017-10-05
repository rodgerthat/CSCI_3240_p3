// Norris, Joel R.
// CSCI_3240
// p3
// Dr. Butler
// A C program that uses the socketpair system call to create
// a pair of sockets, and uses the fork system call to create
// a child heavy-weight process.


#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>


int main( )  {

    int x, rc, status, socketsArray[2];

    char msgArray[100];  // character msgArrayfer, 

    // call the socketpair system function
    socketpair(AF_UNIX, SOCK_STREAM, 0, socketsArray);
    rc = fork();    // fork the process. 

    if (rc > 0) // parent process
    {
        // close the end of the socketsArray inorder to write to the child
        close(socketsArray[1]);

        // loop to read in file and send to child
        while(fgets(msgArray,100,stdin))
        {
        
            int length = 0;

            if(msgArray[0] !='\0')
            {
                write(socketsArray[0], msgArray, 100);
                read(socketsArray[0], msgArray, 100);
                // get length of msg
                // msg is just a string, an array of chars
                // lol this gets the length of the msgArray array 
                // which we already know. neat trick tho. 
                //int length = sizeof(msgArray) / sizeof(msgArray[0]);
                // print msg
                int i;
                for (i=0; i<(sizeof(msgArray)/sizeof(msgArray[0])); ++i) {
                    if (msgArray[i] != '\0') {
                        ++length;
                    } else {
                        break;
                    }
                }
                
                printf("%d: recvd len %d msg: %s:\n", getpid(), (length-1), msgArray);
            }
            else {
                break;
            }
            //read(socketsArray[0],msgArray,100);
            //printf("%d: recvd %s\n",getpid(),msgArray);
        }
        close(socketsArray[0]);

        // wait for the child
        rc = waitpid(rc,&status, 0);
        printf("%d %d\n", rc, status);
    }
    else
    {
        //close the other end of the socket
        close( socketsArray[0] );
        while(x=read(socketsArray[1], msgArray, 100))
        {
            int i;
            for(i=0; i<sizeof(msgArray); ++i)
                    msgArray[i] = tolower(msgArray[i]);
            write(socketsArray[1], msgArray, 100);

        }
        //read(socketsArray[1],msgArray,100); // read the msgArray

        // convert what is in the msgArrayfer to lowercase
        //int i;
        //for(i=0;i<sizeof(msgArray);i++)
        //      {
                //      msgArray[i] = tolower(msgArray[i]);
        //      }
        // :)
        //write(socketsArray[1],msgArray,100);
        msgArray[0] = '\0';
        //rc = read(socketsArray[1],msgArray,100);
        //printf("%d: recvd rc %d  msgArray %s\n",getpid(),rc,msgArray);
        close(socketsArray[1]);
        exit(0);
    }
}
