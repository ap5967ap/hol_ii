#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

union sem{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(){

    int shm_key = ftok(".", 'S');
    int sem_key = ftok(".", 'T');

    int shm_id = shmget(shm_key, 1024, IPC_CREAT | 0666);
    int sem_id = semget(sem_key, 1, IPC_CREAT | 0666);

    union sem inst;
    inst.val = 1;

    int stat = semctl(sem_id, 0, SETVAL, inst);
    if(stat == -1){
        printf("Failed to set semid to 1\n");
        return -1;
    }

    int *shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *)-1){
        printf("Error in shmat call\n");
        return -1;
    }
    
    *shm_ptr = 0;
}