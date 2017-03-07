/*
 * Exercise 5
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MSGPERM 0777

struct msgbuf {
    long mtype;	     /* message type, must be > 0 */
    char mtext[1];	 /* message data */
};

void* thread_filosofo(int *);
int filosofos_id[5], msg_queue_id;

int main(int charc, char* argv[]){
    pthread_t filosofo[5];
    struct msgbuf msg[5];
    char mtext[5] = "Ej5";
    size_t msgsz = sizeof(mtext);

    msg_queue_id = msgget(IPC_PRIVATE, MSGPERM|IPC_CREAT|IPC_EXCL);
    if (msg_queue_id == -1) {
        perror(strerror(errno));
        printf("Ha habido un error creando la cola de mensajes con id = %d\n", msg_queue_id);
        return 1;
    }
    printf("Cola de tenedores %d creada\n\n",msg_queue_id);
    system("ipcs -q");

    for (int i = 0; i < 5; ++i) {
        msg[i].mtype = i+1;
        strcpy(msg[i].mtext, mtext);
        if(msgsnd(msg_queue_id, &(msg[i]), msgsz, IPC_NOWAIT) == -1){
            perror(strerror(errno));
            printf("Ha habido un error enviando el mensaje del tenedor %d\n", i);
            return 1;
        }
        printf("Tenedor %d en la cola.\n", i);
        filosofos_id[i] = i;
    }

    printf("Tenedores en cola.\n");
    system("ipcs -q");
    printf("\n\n");

    for (int j = 1; j < 6; ++j) {
        if(pthread_create(&(filosofo[j]), NULL, (void *)thread_filosofo, &(filosofos_id[j]))){
            printf("No se ha podido crear el filósofo %d", j);
            return 0;
        }
    }

    return 0;
}

void* thread_filosofo(int *id){
    int tenedor_izquierdo = *id, tenedor_derecho;
    printf("Filosofo %d en marcha.\n", tenedor_izquierdo);
    ssize_t return_rcv;
    struct msgbuf msg_izq, msg_der, msg;
    char mtext[5] = "Ej5";
    switch(tenedor_izquierdo){
        case 1:
            tenedor_izquierdo = 1;
            tenedor_derecho = 2;
            break;
        case 2:
            tenedor_izquierdo = 2;
            tenedor_derecho = 3;
            break;
        case 3:
            tenedor_izquierdo = 3;
            tenedor_derecho = 4;
            break;
        case 4:
            tenedor_izquierdo = 4;
            tenedor_derecho = 5;
            break;
        case 5:
            tenedor_izquierdo = 5;
            tenedor_derecho = 1;
            break;
        default:
            break;
    }
    msg_izq.mtype = tenedor_izquierdo;
    msg_der.mtype = tenedor_derecho;
    size_t msgsz = sizeof(mtext);
    strcpy(msg_izq.mtext, mtext);
    strcpy(msg_der.mtext, mtext);
    while(1){
        printf("Filósofo %d deja de pensar e intenta coger tenedor izquierdo.\n", tenedor_izquierdo);
        return_rcv = msgrcv(msg_queue_id, &msg, 5, tenedor_izquierdo, NULL);
        if(return_rcv == 0){
            perror("Ha habido un error: ");
            exit(-1);
        }
        printf("Filósofo %d tiene el tenedor izquierdo. Intentamos coger tenedor derecho.\n", tenedor_izquierdo);
        return_rcv = msgrcv(msg_queue_id, &msg, 5, tenedor_derecho, IPC_NOWAIT);
        if(return_rcv != 5){
            printf("Filósofo %d no ha podido coger el tenedor derecho. Soltando izquierdo.\n", tenedor_izquierdo);
            msgsnd(msg_queue_id, &msg_izq, msgsz, IPC_NOWAIT);
        }else{
            printf("Filósofo %d está comiendo.\n", tenedor_izquierdo);
            usleep(1000000);
            printf("Filósofo %d termina de comer y procede a soltar los tenedores.\n", tenedor_izquierdo);
            msgsnd(msg_queue_id, &msg_der, msgsz, IPC_NOWAIT);
            msgsnd(msg_queue_id, &msg_izq, msgsz, IPC_NOWAIT);
            printf("Filósofo %d ha soltado los tenedores.\n", tenedor_izquierdo);
        }
        printf("Filósofo %d pensando sobre su existencia.\n", tenedor_izquierdo);
        usleep(100000);
    }
}