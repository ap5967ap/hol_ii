#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
    int key=ftok(".",'a');
    if(key==-1)
    {
        perror("ftok");
        return 1;
    }
    int shmid=shmget(key,BUFSIZ,IPC_CREAT|0666);
    if(shmid==-1)
    {
        perror("shmget");
        return 1;
    }
    char *data = shmat(shmid,(void *)0,0);
    if(data==(char *)(-1))
    {
        perror("shmat");
        return 1;
    }
    printf("Enter data to put in shared memory : \n");
    scanf("%[^\n]", data);
    printf("Data written to shared memory => %s\n",data);
    return 0;
}