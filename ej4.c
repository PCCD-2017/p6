/*
 * Exercise 4
 */

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/errno.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

extern int errno;
int msg_queue_id;
#define MSGPERM 0777

struct msgbuf {
    long mtype;	 /* message type, must be > 0 */
    char mtext[30];	 /* message data */
};


int main(int charc, char *argv[]) {
    int queue_id = atoi(argv[1]);
    //       ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

    ssize_t received_msg;
    struct msgbuf msg;
    char charsize[30];
    size_t size = sizeof(charsize);
    received_msg = msgrcv(queue_id, &msg, size, 0, MSG_NOERROR);

    if(received_msg == 0){
        perror(strerror(errno));
        printf("Ha habido un error leyendo un mensaje de la cola de mensajes con id = %d\n", queue_id);
        return 1;
    }else{
        printf("Mensaje recibido con éxito. Cola: \n");
        printf("El mensaje recibido es: %s \n", msg.mtext);
        system("ipcs -q");
    }

    return 0;
}
