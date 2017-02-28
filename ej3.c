/*
 * Exercise 3
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

int return_msgsnd;

struct msgbuf {
    long mtype;	 /* message type, must be > 0 */
    char mtext[1];	 /* message data */
};


int main(int charc, char *argv[]) {
    int queue_id = atoi(argv[1]);

    //       int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
    //       ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

    /*
     The  mtext  field  is an array (or other structure) whose size is specified by
       msgsz, a nonnegative integer value.  Messages of zero length (i.e.,  no	mtext
       field)  are  permitted.	The mtype field must have a strictly positive integer
       value.  This value can be used by the receiving process for message  selection
       (see the description of msgrcv() below).
    */

    struct msgbuf msg;
    msg.mtype = 1;
    char mtext[30] = "Mensaje de prueba, ejercicio 3.";
    strcpy(msg.mtext, mtext);
    size_t msgsz = sizeof(mtext);

    return_msgsnd = msgsnd(queue_id, &msg, msgsz, IPC_NOWAIT);

    if(return_msgsnd<0){
        perror(strerror(errno));
        printf("Ha habido un error enviando un mensaje a la cola de mensajes con id = %d\n", queue_id);
        return 1;
    }else{
        printf("Mensaje enviado con éxito. Cola: \n");
        system("ipcs -q");
    }

    return 0;
}
