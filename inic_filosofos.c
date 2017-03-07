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


int main(int charc, char* argv[]){
    char input[32];
    pthread_t filosofo[5];
    struct msgbuf msg[5];
    char mtext[5] = "Ej5";
    size_t msgsz = sizeof(mtext);
    int msg_queue_id;

    msg_queue_id = msgget(IPC_PRIVATE, MSGPERM|IPC_CREAT|IPC_EXCL);
    if (msg_queue_id == -1) {
        perror(strerror(errno));
        printf("Ha habido un error creando la cola de mensajes con id = %d\n", msg_queue_id);
        return 1;
    }
    printf("Cola de tenedores %d creada\n\n",msg_queue_id);
    system("ipcs -q");
    printf("Pulse ENTER cuando haya inicializado los 5 filósofos.\n");
    fgets(input, sizeof(input), stdin);
    for (int i = 0; i < 5; ++i) {
        msg[i].mtype = i+1;
        strcpy(msg[i].mtext, mtext);
        if(msgsnd(msg_queue_id, &(msg[i]), msgsz, IPC_NOWAIT) == -1){
            perror(strerror(errno));
            printf("Ha habido un error enviando el mensaje del tenedor %d\n", i);
            return 1;
        }
        printf("Tenedor %d en la cola.\n", i);
    }

    printf("Tenedores en cola.\n");
    system("ipcs -q");
    printf("\n\n");

    return 0;
}