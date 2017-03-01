/*
 * Exercise 4
 */

#include<sys/types.h>
#include<sys/msg.h>
#include<sys/errno.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGPERM 0777

/**
 *  ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
 *
 *  1.- msqid: the msgrcv() system call removes a message
 *      from the queue specified by msquid (ID queue).
 *
 *  2.- *msgp: put the message in the buffer pointed to by msgp.
 *
 *  3.- msgsz: The argument msgsz specifies the maximum size in bytes for
 *      the member mtext of the structure pointed to by the msgp argument
 *
 *  4.- msgtyp: If msgtyp is 0, then the first message in the queue is read.
 *
 *  5.- msgflg:
 *
 *      IPC_NOWAIT: Return immediately if no message of the requested type is
 *      in the queue. The system call fails with errno set to ENOMSG.
 *
 *      MSG_EXCEPT: Used with msgtyp greater than 0 to read the first message
 *      in the queue with message type that differs from msgtyp.
 *
 *      MSG_NOERROR: To truncate the message text if longer than msgsz bytes.
 *
 *      @note: If no message of the requested type is available and IPC_NOWAIT
 *      isn't specified in msgflg, the calling process is blocked until one of
 *      the following conditions occurs:
 *
 *          a) A message of the desired type is placed in the queue.
 *          b) The message queue is removed from the system.
 *             In this case the system call fails with errno set to EIDRM.
 *          c) The calling process catches a signal. In this case the system
 *             call fails with errno set to EINTR.
 *
 *
 * @note: The msgp argument is a pointer to caller-defined structure of the following general form:
 *
 *      struct msgbuf {
 *          long mtype;       message type, must be > 0
 *          char mtext[1];    message data
 *      };
 */

struct msgbuf {
    long mtype;	 /* message type, must be > 0 */
    char mtext[30];	 /* message data */
};

int main(int charc, char *argv[]) {
    int queue_id = atoi(argv[1]);
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
