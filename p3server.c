#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


int server(int sock)
{
    int i, msg_size, num_msgs;
    char first_char, last_char;
    char msg_to_send[64], ack[8];

    num_msgs = atoi( getenv("P3_NUM_MSGS") );
    first_char = *( getenv("P3_FIRST_CHAR") );
    last_char  = *( getenv("P3_LAST_CHAR") );

    srand( num_msgs );

    for (i=0; i < num_msgs; i++)
    {
        memset(msg_to_send,'-',64);
        msg_to_send[63] = '\0';  // just for debug print below
        msg_size = rand() % 30 + 10;  // between 10 and 40 bytes
        sprintf(msg_to_send,"%04d",msg_size);
        msg_to_send[4] = first_char;
        msg_to_send[msg_size+4-1] = last_char;
        printf("SERVER  len %d  msg :%s:\n",msg_size,msg_to_send);
        write(sock,msg_to_send,msg_size+4);
        read(sock,ack,6);
        if ( strncmp(ack,"ack ",4) != 0  || ack[4] != first_char || ack[5] != last_char)
        {
            ack[6] = '\0';
            printf("**** exiting;  invalid ack recvd from client :%s:\n",ack);
            exit(-1);
        }
        sleep(1);
    }

    exit(0);    // <--- NOTE that this function does NOT return
}
