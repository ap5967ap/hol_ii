#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>

union sem{
    int val;
    struct semid_ds *buf;
    unsigned short int *arr;
};


int main(){

    union sem inst;
    key_t key = ftok(".", 'a');
    int semid = semget(key, 1, 0);
    semctl(semid, 0, IPC_RMID, inst);
    return (0);
}