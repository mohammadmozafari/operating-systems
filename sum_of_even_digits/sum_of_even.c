#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    pid = fork();
    
    if (pid < 0)
    {
        printf("failed to fork the process\n");
    }
    else if (pid == 0)
    {
        printf("this is child process\n");
    }
    else
    {
        printf("this is parent process\n");
    }
    
    return 0;
}