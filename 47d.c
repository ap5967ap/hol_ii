#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define pr perror

int main()
{
    int key=ftok(".",'a');
    if(key==-1)
    {
        pr("ftok");
        return 1;
    }
    int shmid = shmget(key,0,0);
    if(shmid==-1)
    {
        pr("shmget");
        return 1;
    }
    if(shmctl(shmid,IPC_RMID,NULL)==-1)
    {
        pr("shmctl");
        return 1;
    }
    printf("Deleted\n");
    return 0;
}
