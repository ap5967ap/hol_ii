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
    int msgid=msgget(key,IPC_CREAT|0666);
    struct msgbuf msg;
    msg.mtype=1;
    pt("Enter the message to send using message queue: \n");
    scanf("%[^\n]",msg.mtext);
    if(msgsnd(msgid,(struct msgbuf *)&msg,BUFSIZ,0)==-1)
    {
        pr("msgsnd");
        return 1;
    }

}
