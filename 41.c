#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#define pr perror
#define pt(a) printf("%s\n",a)

int main()
{
    int key=ftok(".",'a');
    if(key==-1)
    {
        pr("ftok");
        return 1;
    }
    int msgid=msgget(key,IPC_CREAT|0666);
    printf("Key is %d, queue id is %d\n",key,msgid);
}