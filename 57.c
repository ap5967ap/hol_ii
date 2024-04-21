#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#define ll long long
void pt(char *x, int a){printf("%s => %d\n",x,a);}

int main()
{
    pt("Maximum length of arguments in the exec family of functions",sysconf(_SC_ARG_MAX));
    pt("Maximum number of simultaneous processes per user ID",sysconf(_SC_CHILD_MAX));
    pt("Number of clock ticks per second",sysconf(_SC_CLK_TCK));
    pt("Maximum number of open files",sysconf(_SC_OPEN_MAX));
    pt("size of a page",sysconf(_SC_PAGESIZE));
    pt("Total number of pages in the physical memor", sysconf(_SC_PHYS_PAGES));
    pt("Number of currently available pages in the physical memory", sysconf(_SC_AVPHYS_PAGES));
}