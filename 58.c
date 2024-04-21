#define _GNU_SOURCE
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>


void* thrd()
{
    printf("Thread with id %d\n", gettid());
}

int main()
{
    pthread_t t1,t2,t3;
    pthread_create(&t1,NULL,thrd,NULL);
    pthread_create(&t2,NULL,thrd,NULL);
    pthread_create(&t3,NULL,thrd,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    return 0;
}