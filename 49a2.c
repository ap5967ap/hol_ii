#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>

struct ticket{
    char *name;
    int num;
};

struct sembuf op;

int main(){

    int fd = open("tickets.txt", O_RDWR);

    if (fd == -1){
        printf("Unable to open file\n");
        return -1;
    }

    int key = ftok(".", 'a');
    int sem_id = semget(key, 1, 0);

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;

    printf("Locking\n");

    int ret = semop(sem_id, &op, 1);

    if (ret == -1){
        printf("Lock failed!s\n");
        return -1;
    }

    printf("Locked\n");

    struct ticket ticket1;
    read(fd, &ticket1, sizeof(struct ticket));

    printf("Current ticket number: %d\n", ticket1.num);

    ticket1.num += 1;
    lseek(fd, 0, SEEK_SET);
    write(fd, &ticket1, sizeof(struct ticket));

    lseek(fd, 0, SEEK_SET);
    read(fd, &ticket1, sizeof(struct ticket));

    printf("Incremented ticket number: %d\n", ticket1.num);

    printf("press enter to unlock\n");
    char ch;
    scanf("%c", &ch);

    op.sem_op = 1;
    int stat = semop(sem_id, &op, 1);

    printf("Unlocked\n");

    close(fd);
}