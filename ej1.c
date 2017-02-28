/*
 * Exercise 1
 */

#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<sys/errno.h>

extern int errno;
int msg_queue_id;
#define MSGPERM 0777

int main(int charc, char* argv[]){
    //        int msgget(key_t key, int msgflg);
    msg_queue_id = msgget(IPC_PRIVATE, MSGPERM|IPC_CREAT|IPC_EXCL);

    if (msg_queue_id < 0) {
        perror(strerror(errno));
        printf("Ha habido un error creando la cola de mensajes con id = %d\n", msg_queue_id);
        return 1;
    }
    printf("Cola de mensajes %d creada\n",msg_queue_id);
    system("ipcs -q");


    return 0;
}