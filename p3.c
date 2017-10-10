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


int main( int argc, char **argv )  {

    pid_t pid;
    int rc, status, sock[2], n;
    char msg[100];
    char response[8];
    socketpair( AF_UNIX, SOCK_STREAM, 0, sock);
    printf( "fds= %d %d\n", sock[0], sock[1] );
    pid = fork();

    if ( pid > 0 ) {
        
        close( sock[1] );

        while( read( sock[0], msg, 4 ) ) {

            msg[4] = '\0';
            n = atoi( msg );
            read( sock[0], msg, n);
            sprintf( response, "ack %c %c", msg[0], msg[n-1] );
            write( sock[0], response, 6 );
            msg[n] = '\0';
            printf( "CLIENT rcvd len %d msg :%s: ", n, msg );
        }
        wait(&status);
    } else {
        close( sock[0] );
        server( sock[1] );

    }
        

}
