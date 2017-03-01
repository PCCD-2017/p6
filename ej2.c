/*
 * Exercise 2
 */

#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/errno.h>
#include<stdio.h>
#include <stdlib.h>

/**
 * int msgctl(int msqid, int cmd, struct msqid_ds *buf);
 *
 * > msgctl() performs the control operation specified by cmd on the message queue with identifier msqid.
 *
 * cmd:
 *
 * 1.- IPC_STAT: Copy information from the kernel data structure associated with msqid into the msqid_ds
 * structure pointed to by buf. The caller must have read permission on the message queue.
 *
 * 2.- IPC_SET: Write the values of some members of the msqid_ds structure pointed to by buf to the kernel
 * data structure associated with this message queue, updating also its msg_ctime member. The following
 * members of the structure are updated: msg_qbytes, msg_perm.uid, msg_perm.gid, and (the least significant
 * 9 bits of) msg_perm.mode. The effective UID of the calling process must match the owner (msg_perm.uid) or
 * creator (msg_perm.cuid) of the message queue, or the caller must be privileged. Appropriate privilege
 * (Linux: the CAP_IPC_RESOURCE capability) is required to raise the msg_qbytes value beyond the system
 * parameter MSGMNB.
 *
 * 3.- IPC_RMID: Immediately remove the message queue, awakening all waiting reader and writer processes
 * (with an error return and errno set to EIDRM). The calling process must have appropriate privileges or
 * its effective user ID must be either that of the creator or owner of the message queue.
 *
 * 4.- IPC_INFO (Linux-specific): Returns information about system-wide message queue limits and parameters
 * in the structure pointed to by buf. This structure is of type msginfo (thus, a cast is required), defined
 * in <sys/msg.h> if the _GNU_SOURCE feature test macro is defined:
 *
 *      struct msginfo {
 *          int msgpool;                            Size in kibibytes of buffer pool used to hold message data;
 *                                                  unused within kernel
 *          int msgmap;                             Maximum number of entries in message map; unused within kernel
 *          int msgmax;                             Maximum number of bytes that can be written in a single message
 *          int msgmnb;                             Maximum number of bytes that can be written to queue; used to
 *                                                  initialize msg_qbytes during queue creation   (msgget(2))
 *          int msgmni;                             Maximum number of message queues
 *          int msgssz;                             Message segment size;  unused within kernel
 *          int msgtql;                             Maximum number of messages on all queues in system; unused within kernel
 *          unsigned short int msgseg;              Maximum number of segments unused within kernel
 *      };
 *
 * ---------------------------------------------------------------------------------------------------------------------
 * msqid_ds:
 *      struct msqid_ds {
 *          struct ipc_perm msg_perm;     Ownership and permissions
 *          time_t          msg_stime;    Time of last msgsnd(2)
 *          time_t          msg_rtime;    Time of last msgrcv(2)
 *          time_t          msg_ctime;    Time of last change
 *          unsigned long   __msg_cbytes; Current number of bytes in queue (nonstandard)
 *          msgqnum_t       msg_qnum;     Current number of messages in queue
 *          msglen_t        msg_qbytes;   Maximum number of bytes allowed in queue
 *          pid_t           msg_lspid;    PID of last msgsnd(2)
 *          pid_t           msg_lrpid;    PID of last msgrcv(2)
 *      };
 *
 * The ipc_perm structure is defined as follows (the highlighted fields are settable using IPC_SET):
 *      struct ipc_perm {
 *          key_t          __key;       Key supplied to msgget(2)
 *          uid_t          uid;         Effective UID of owner
 *          gid_t          gid;         Effective GID of owner
 *          uid_t          cuid;        Effective UID of creator
 *          gid_t          cgid;        Effective GID of creator
 *          unsigned short mode;        Permissions
 *          unsigned short __seq;       Sequence number
 *       };
 */

int main(int charc, char* argv[]){
    int return_msgctl, queue_id = atoi(argv[1]);

    return_msgctl = msgctl(queue_id, IPC_RMID, NULL);
    if(return_msgctl == 0){
        printf("La cola de mensajes se ha eliminado con éxito.\n");
        system("ipcs -q");
    }else{
        perror(strerror(errno));
        printf("Ha habido un error eliminando la cola de mensajes con id = %d\n", queue_id);
        return 1;
    }
    return 0;
}