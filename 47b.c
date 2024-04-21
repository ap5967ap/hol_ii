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
    int shmid=shmget(key,0,0);
    char *data = shmat(shmid, (void *)0, SHM_RDONLY);
    if(data==(char *)(-1))
    {
        pr("shmat");
        return 1;
    }
    printf("Data read from shared memory => %s\n",data);
    // strcpy(data,"Hello from 47b.c");  // gives segmentation fault
    // if(strcmp(data,"Hello from 47b.c")==0)
    //     printf("Data written to shared memory => %s\n",data);
    // else
    //     printf("Data not written to shared memory as expected\n");
}