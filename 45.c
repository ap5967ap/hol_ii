#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <time.h>
#define pr perror
#define pt printf
struct msgbuf
{
    long mtype;
    char mtext[BUFSIZ];
};

int main()
{
    int key=ftok(".",'a');
    if(key==-1)
    {
        pr("ftok");
        return 1;
    }
    int msgid=msgget(key,0);
    struct msqid_ds buf;
    msgctl(msgid,IPC_STAT,&buf);
    printf("Access permissions: %o\n",buf.msg_perm.mode);

    buf.msg_perm.mode = 0777;
    msgctl(msgid,IPC_SET,&buf);
    struct msqid_ds buf2;
    msgctl(msgid,IPC_STAT,&buf2);
    printf("Now, after setting access permissions: %o\n",buf2.msg_perm.mode);
}