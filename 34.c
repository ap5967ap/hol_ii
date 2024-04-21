#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#define pr perror
#define pt(a) printf("%s\n",a)
#define pt1(a) printf("%d\n",a)

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        pt("Usage: ./a.out dup|dup2|fnctl");
        return 1;
    }
    int fd[2];
    if(pipe(fd) == -1)
    {
        pr("pipe");
        return 1;
    }
    if(strcmp(argv[1],"dup")==0)
    {
        if(!fork())
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			execl("/bin/ls", "/bin/ls", "-l", NULL);
		}
		else
		{
            wait(NULL);
			close(0);
			close(fd[1]);
			dup(fd[0]);
			execl("/bin/ls", "/bin/ls", "-l", NULL);

		}
    }
    else if(strcmp(argv[1],"dup2")==0)
    {
        if(!fork())
        {
            close(fd[0]);
            dup2(fd[1],1);
            execl("/bin/ls", "/bin/ls", "-l", NULL);
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            dup2(fd[0],0);
            execl("/bin/ls", "/bin/ls", "-l", NULL);

        }
    }
    else if(strcmp(argv[1],"fcntl")==0)
    {
        if(!fork())
        {
			close(1);
            close(fd[0]);
			fcntl(fd[1], F_DUPFD, 1);
			execl("/bin/ls", "/bin/ls", "-l", NULL);
        }
        else
        {
            wait(NULL);
            close(0);
			close(fd[1]);
			fcntl(fd[0], F_DUPFD, 0);
			execl("/bin/ls", "/bin/ls", "-l", NULL);

        }
    }
    else
    {
        pt("Invalid option");
        return 1;
    }
}