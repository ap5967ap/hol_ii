#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#define pr perror

int main()
{
    int key=ftok(".",'a');
    if(key==-1)
    {
        pr("ftok");
        return 1;
    }
    int i=0;
    int shmid=shmget(key,0,0);
    char *data = shmat(shmid, (void *)0, SHM_RDONLY);
    printf("Press enter to detach\n");
    getchar();
    if(shmdt(data)==-1)
    {
        pr("shmdt");
        return 1;
    }
    printf("Detached\n");
    return 0;

}