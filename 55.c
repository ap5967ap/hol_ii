#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main()
{
    struct rlimit rlim;
    printf("Old limits\n");
    getrlimit(RLIMIT_NICE, &rlim);

    printf("Soft - %lu\n", rlim.rlim_cur);
    printf("Hard - %lu\n", rlim.rlim_max);

    rlim.rlim_cur = 5;
    rlim.rlim_max = 7;

    if (setrlimit(RLIMIT_NICE, &rlim) != -1)
    {
        printf("New limits\n");
        getrlimit(RLIMIT_NICE, &rlim);

        printf("Soft - %lu\n", rlim.rlim_cur);
        printf("Hard - %lu\n", rlim.rlim_max);
    }
    else
    {
        perror("Error");
    }

    return(0);
}