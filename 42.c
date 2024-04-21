#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <time.h>
#define pr perror
int main()
{
    int key=ftok(".",'a');
    if(key==-1)
    {
        pr("ftok");
        return 1;
    }
    int msgid=msgget(key,IPC_CREAT|0666);
    struct msqid_ds buf;
    if(msgctl(msgid,IPC_STAT,&buf)==-1)
    {
        pr("msgctl");
        return 1;
    }
    /**
     * 0400   Read by user
       0200   Write by user
       0040   Read by group
       0020   Write by group
       0004   Read by others
       0002   Write by others
     */
    //access permissions of the message queue
    printf("Access permissions: %o\n",buf.msg_perm.mode);
    //permission of the message queue
    printf("Owner's effective UID: %d\n",buf.msg_perm.uid);
    printf("Owner's effective GID: %d\n",buf.msg_perm.gid);
    //. Time of last message sent and received 
    printf("Time of last message sent: %s",ctime(&buf.msg_stime));
    printf("Time of last message received: %s",ctime(&buf.msg_rtime));
    //Time of last change in the message queue 
    printf("Time of last change: %s",ctime(&buf.msg_ctime));
    // Size of the queue 
    printf("Size of the queue: %ld\n",buf.msg_qnum);
    //Number of messages in the queue 
    printf("Number of messages in the queue: %ld\n",buf.msg_qnum);
    //Maximum number of bytes allowed in the queue
    printf("Maximum number of bytes allowed in the queue: %ld\n",buf.msg_qbytes);
    //PID of the last process that sent a message
    printf("Pid of the last msgsnd and msgrcv - %d %d\n", buf.msg_lspid, buf.msg_lrpid);

}