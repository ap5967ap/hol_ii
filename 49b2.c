#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

struct sembuf sops;

int main(){

    int shm_key = ftok(".", 'S');
    int sem_key = ftok(".", 'T');

    int shm_id = shmget(shm_key, 1024, 0);

    int *shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *)-1){
        printf("Error in shmat call\n");
        return -1;
    }

    int sem_id = semget(sem_key, 1, 0);
    if (sem_id == -1){
        printf("Error in semget system call\n");
        return -1;
    }

    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = 0;

    printf("Before : counter = %d\n", *shm_ptr);

    if (semop(sem_id, &sops, 1) == -1){
        printf("Error in semop system call\n");
        return -1;
    }

    int temp = *shm_ptr;
    temp++;
    *shm_ptr = temp;

    printf("After: counter = %d\n", *shm_ptr);

    printf("Press enter to unlock");
    char ch;
    scanf("%c", &ch);

    sops.sem_op = 1;
    if (semop(sem_id, &sops, 1) == -1)
    {
        printf("Error in semop system call\n");
        return -1;
    }

    if (shmdt(shm_ptr) == -1){
        printf("Error in shmdt system call\n");
        return -1;
    }

    return 0;
}

