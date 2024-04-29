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
    //cat /proc/cpuinfo for cpu frequency
    printf("Time: %f ms\n", (end - st)/(1087.806 * 1e6));
    
}