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
    if(msgctl(msgid,IPC_RMID,0)==-1)
    {
        pr("msgctl");
        return 1;
    }

}