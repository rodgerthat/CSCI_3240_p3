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

        int x,rc, status, sock[2];

        char buf[100];  // character buffer, 
        // call the socketpair system function
        socketpair(AF_UNIX,SOCK_STREAM,0,sock);
        rc = fork();

        //printf("Before the if/else stuff");
        if (rc > 0) // parent process
        {
                // close the end of the sock inorder to write to the child
                close(sock[1]);

                //printf("before the while loop");
                // loop to read in file and send to child
                while(fgets(buf,100,stdin))
                {
                        if(buf[0] !='\0')
                        {
                                write(sock[0],buf,100);
                                read(sock[0],buf,100);
                                printf("%d: recvd %s\n", getpid(), buf);
                        }
                        //read(sock[0],buf,100);
                        //printf("%d: recvd %s\n",getpid(),buf);
                        else
                                break;
                }
                close(sock[0]);

                // wait for the child
                rc = waitpid(rc,&status,0);
                printf("%d %d\n",rc,status);
        }
        else
        {
                //close the other end of the socket
                close(sock[0]);
                while(x=read(sock[1],buf,100))
                {
                        int i;
                        for(i=0;i<sizeof(buf);i++)
                                buf[i] = tolower(buf[i]);
                        write(sock[1],buf,100);

                }
                //read(sock[1],buf,100); // read the buf

                // convert what is in the buffer to lowercase
                //int i;
                //for(i=0;i<sizeof(buf);i++)
        //      {
                //      buf[i] = tolower(buf[i]);
        //      }
                // :)
                //write(sock[1],buf,100);
                buf[0] = '\0';
                //rc = read(sock[1],buf,100);
                //printf("%d: recvd rc %d  buf %s\n",getpid(),rc,buf);
                close(sock[1]);
                exit(0);
        }
}
