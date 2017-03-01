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

#define MSGPERM 0777

/**
 * int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
 *
 * 1.- The msgsnd() system call appends a copy of the message
 *     pointed to by msgp to the message queue whose identifier is specified by msqid.
 *
 * 2.- If sufficient space is available in the queue, msgsnd() succeeds immediately.
 *     (The queue capacity is defined by the msg_qbytes field in the associated data
 *     structure for the message queue. During queue creation this field is initialized
 *     to MSGMNB bytes, but this limit can be modified using msgctl(2).)
 *
 * 3.- msgflag: If insufficient space is available in the queue, then the default behavior
 *     of msgsnd() is to block until space becomes available. If IPC_NOWAIT is specified
 *     in msgflg, then the call instead fails with the error EAGAIN.
 *
 * @note: A blocked msgsnd() call may also fail if:
 *
 *          a) The queue is removed, in which case the system call fails with errno set to EIDRM.
 *          b) A signal is caught, in which case the system call fails with errno set to EINTR.
 *             ((msgsnd() is never automatically restarted after being interrupted by a signal handler).
 *
 * @note: The msgp argument is a pointer to caller-defined structure of the following general form:
 *
 *      struct msgbuf {
 *          long mtype;       message type, must be > 0
 *          char mtext[1];    message data
 *      };
 */

struct msgbuf {
    long mtype;	     /* message type, must be > 0 */
    char mtext[1];	 /* message data */
};

int main(int charc, char *argv[]) {
    int return_msgsnd, queue_id = atoi(argv[1]);
    struct msgbuf msg;
    char mtext[30] = "Mensaje de prueba, ejercicio 3.";

    msg.mtype = 1;
    strcpy(msg.mtext, mtext);
    size_t msgsz = sizeof(mtext);

    return_msgsnd = msgsnd(queue_id, &msg, msgsz, IPC_NOWAIT);
    if(return_msgsnd == -1){
        perror(strerror(errno));
        printf("Ha habido un error enviando un mensaje a la cola de mensajes con id = %d\n", queue_id);
        return 1;
    }else{
        printf("Mensaje enviado con éxito. Cola: \n");
        system("ipcs -q");
    }
    return 0;
}
