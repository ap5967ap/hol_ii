#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

struct sembuf sops;

int main(){

    int shm_key = ftok(".", 'C');
    int shm_key2 = ftok(".", 'D');
    int sem_key = ftok(".", 'E');

    int shm_id = shmget(shm_key, 1024, 0);
    int shm_id2 = shmget(shm_key2, 1024, 0);

    if (shm_id == -1 || shm_id2 == -1){
        printf("Error in shmget call\n");
        return -1;
    }

    int *shm_ptr = shmat(shm_id, NULL, 0);
    int *shm_ptr2 = shmat(shm_id2, NULL, 0);

    if (shm_ptr == (void *)-1 || shm_ptr2 == (void *)-1){
        printf("Error in shmat call\n");
        return -1;
    }

    int sem_id = semget(sem_key, 1, 0);

    if (sem_id == -1){
        printf("Error in semget system call\n");
        return -1;
    }

    sops.sem_flg = SEM_UNDO;

    printf("Before critical section : counter 1 = %d, counter 2 = %d\n", *shm_ptr, *shm_ptr2);

    // LOCKING TWICE - COUNTING SEMAPHORE ACCESS TO 2 Resouces
    sops.sem_num = 0;
    sops.sem_op = -1;

    if (semop(sem_id, &sops, 1) == -1){
        printf("Error in semop system call\n");
        return -1;
    }

    int temp = *shm_ptr;
    temp++;
    *shm_ptr = temp;

    printf("During critical section after 1 operation: counter 1 = %d, counter 2 = %d\n", *shm_ptr, *shm_ptr2);

    sops.sem_num = 0;
    sops.sem_op = -1;
    if (semop(sem_id, &sops, 1) == -1)
    {
        printf("Error in semop system call\n");
        return -1;
    }

    temp = *shm_ptr2;
    temp++;
    *shm_ptr2 = temp;

    printf("During critical section after 2 operation: counter 1 = %d, counter 2 = %d\n", *shm_ptr, *shm_ptr2);

    printf("Press enter to unlock\n");
    char ch;
    scanf("%c", &ch);

    // UNLOCK TWICE
    sops.sem_op = 1;
    if (semop(sem_id, &sops, 1) == -1)
    {
        printf("Error in semop system call\n");
        return -1;
    }

    sops.sem_op = 1;
    if (semop(sem_id, &sops, 1) == -1)
    {
        printf("Error in semop system call\n");
        return -1;
    }

    // Detach the shared memory segments from process address space
    if (shmdt(shm_ptr) == -1 || shmdt(shm_ptr2) == -1){
        printf("Error in shmdt call\n");
        return -1;
    }

    return 0;
}