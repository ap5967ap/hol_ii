#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<time.h>
#define ll long long

unsigned long long rdtsc()
{
    unsigned long long dst;
    __asm__ __volatile__("rdtsc" : "=A"(dst));
    return dst;
}

int main()
{
    ll st,end;
    st = rdtsc();
    for (int i = 0; i < 100; i++)
    {
        getppid();
    }
    end = rdtsc();
    printf("Time: %f\n ms", (end - st)/(400 * 1e6));
    
}