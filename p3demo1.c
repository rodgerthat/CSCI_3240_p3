#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

main()
{
    int rc, status, sock[2];
    char buf[1000];

    socketpair(AF_UNIX,SOCK_STREAM,0,sock);
    printf("fds = %d %d\n",sock[0],sock[1]);
    rc = fork();
    printf("rc=%d\n",rc);
    if (rc > 0)
    {
        close(sock[1]);
        read(sock[0],buf,4);
        buf[4] = '\0';  //   just for debugging
        printf("LEN %s\n",buf);
        rc = wait(&status);
        printf("status of child %d\n",status);
    }
    else
    {
        close(sock[0]);
        server(sock[1]);
    }
}
