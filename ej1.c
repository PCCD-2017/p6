/*
 * Exercise 1
 */

#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGPERM 0777

/**
 * CREATE A NEW QUEQUE:
 *
 * int msgget(key_t key, int msgflg);
 *
 * 1.- key: A new message queue is created if key has the value IPC_PRIVATE
 *          or key isn't IPC_PRIVATE, no message queue with the given key key exists.
 *          IPC_PRIVATE isn't a flag field but a key_t type. If this special value is
 *          used for key, the system call ignores everything but the least significant
 *          9 bits of msgflg and creates a new message queue (on success)
 *
 * 2.- msgflag: If msgflg specifies both IPC_CREAT and IPC_EXCL and a message queue already
 *              exists for key, then msgget() fails with errno set to EEXIST.
 *
 * 3.- Upon creation, the least significant bits of the argument msgflg define the permissions
 *     of the message queue. These permission bits have the same format and semantics as the
 *     permissions specified for the mode argument of open(2). (The execute permissions are not used.)
 */

int main(int charc, char* argv[]){
    int msg_queue_id;

    msg_queue_id = msgget(IPC_PRIVATE, MSGPERM|IPC_CREAT|IPC_EXCL);
    if (msg_queue_id == -1) {
        perror(strerror(errno));
        printf("Ha habido un error creando la cola de mensajes con id = %d\n", msg_queue_id);
        return 1;
    }
    printf("Cola de mensajes %d creada\n",msg_queue_id);
    system("ipcs -q");


    return 0;
}