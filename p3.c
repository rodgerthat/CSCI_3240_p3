// Norris, Joel R.
// CSCI_3240
// p3
// Dr. Butler
// A C program that uses the socketpair system call to create
// a pair of sockets, and uses the fork system call to create
// a child heavy-weight process.
// set environment variables
// export P3_NUM_MSGS=1
// export P3_FIRST_CHAR=A
// export P3_LAST_CHAR=Z


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>


int main()  {

    int pid, rc, status, sock[2], i;
    char buf[1000], recvd[8];
    socketpair( AF_UNIX, SOCK_STREAM, 0, sock);
    printf( "fds= %d %d\n", sock[0], sock[1] );
    pid = fork();

    if ( pid > 0 ) {
        
        close( sock[1] );

        while( read( sock[0], buf, 4 ) ) {

            buf[4] = '\0';
            i = atoi( buf );
            read( sock[0], buf, i);
            sprintf( recvd, "ack %c %c", buf[0], buf[i-1] );
            write( sock[0], recvd, 6 );
            buf[i] = '\0';
            printf( "CLIENT recvd len %d buf :%s: \n", i, buf );
        }

        wait(&status);

    } else {

        close( sock[0] );
        server( sock[1] );

    }

}
