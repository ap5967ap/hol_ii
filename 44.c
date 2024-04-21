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
    int choice = -1;
    printf("Choose a flag:\n1.) Use 0 as flag\n2.) Use IPC_NOWAIT as flag\n=> ");
    scanf("%d", &choice);
    struct msgbuf msg;
    if(choice==1)
    {
        int type;
        printf("Enter message type:\n");
        scanf("%d", &type);
        if(msgrcv(msgid,(struct msgbuf *)&msg,BUFSIZ,type,0)==-1)
        {
            pr("msgrcv");
            return 1;
        }
        printf("Message received: %s\n", msg.mtext);
    }
    else if(choice==2)
    {
        int type;
        printf("Enter message type:\n");
        scanf("%d", &type);
        if(msgrcv(msgid,(struct msgbuf *)&msg,BUFSIZ,type,IPC_NOWAIT)==-1)
        {
            pr("msgrcv");
            return 1;
        }
        printf("Message received: %s\n", msg.mtext);
    }
    else
    {
        printf("Invalid choice\n");
    }
}