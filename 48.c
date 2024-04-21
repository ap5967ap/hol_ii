#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

union semun
{
    int val;                   // Value for SETVAL
    struct semid_ds *buf;      // Buffer for IPC_STAT, IPC_SET.
    unsigned short int *array; // Array for GETALL, SETALL.
};

int main()
{
    union semun arg;
    int key=ftok(".",'a');
    int semid=semget(key,1,IPC_CREAT|0666);
    int choice;
    printf("Choose an option:\n1.) Binary Semaphore\n2.) Counting Semaphore\n=> ");
    scanf("%d", &choice);
    if(choice==1)
    {
        printf("Binary Semaphore\n");
        arg.val=1;
        semctl(semid,0,SETVAL,arg);
    }
    else if(choice==2)
    {
        printf("Counting Semaphore\n");
        arg.val=5;
        semctl(semid,0,SETVAL,arg);
    }
}