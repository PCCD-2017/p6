#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

struct msgbuf {
    long mtype;         /* message type, must be > 0 */
    char mtext[1];     /* message data */
};

int main(int charc, char *argv[]) {
    int tenedor_izquierdo = atoi(argv[1]);
    int tenedor_derecho = atoi(argv[2]);
    int comedor_queue_id = atoi(argv[3]);
    printf("Filosofo %d en marcha.\n", tenedor_izquierdo);
    ssize_t return_rcv;
    struct msgbuf msg_izq, msg_der, msg;
    char mtext[5] = "Ej5";

    msg_izq.mtype = 1;
    msg_der.mtype = 1;
    msg.mtype = 1;
    size_t msgsz = sizeof(mtext);
    strcpy(msg_izq.mtext, mtext);
    strcpy(msg_der.mtext, mtext);
    strcpy(msg.mtext, mtext);
    while (1) {
        printf("******************\nFilósofo pensando.\n******************\n");
        return_rcv = msgrcv(comedor_queue_id, &msg, 5, 1, NULL);
        if (return_rcv == 0) {
            perror("Ha habido un error: ");
            exit(-1);
        }
        msgrcv(tenedor_izquierdo, &msg, 5, 1, NULL);
        msgrcv(tenedor_derecho, &msg, 5, 1, NULL);
        printf("******************\nFilósofo comiendo.\n******************\n");
        usleep(1000000);
        msgsnd(tenedor_derecho, &msg_der, msgsz, IPC_NOWAIT);
        msgsnd(tenedor_izquierdo, &msg_izq, msgsz, IPC_NOWAIT);
        msgsnd(comedor_queue_id, &msg, msgsz, IPC_NOWAIT);
        usleep(100000);
    }
}