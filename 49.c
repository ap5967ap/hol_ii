#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
    int key=ftok(".",'a');
    int semid=semget(key,1,IPC_CREAT|0666);
        
}