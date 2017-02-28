/*
 * Exercise 2
 */

#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/errno.h>
#include<stdio.h>

extern int errno;
int msg_queue_id;
int return_msgctl;

int main(int charc, char* argv[]){
    int queue_id = atoi(argv[1]);

    //       int msgctl(int msqid, int cmd, struct msqid_ds *buf);

    return_msgctl = msgctl(queue_id, IPC_RMID, NULL);
    if(return_msgctl == 0){
        printf("La cola de mensajes se ha eliminado con éxito.\n");
        system("ipcs -q");
    }else if(return_msgctl<0){
        perror(strerror(errno));
        printf("Ha habido un error eliminando la cola de mensajes con id = %d\n", queue_id);
        return 1;
    }
    return 0;
}