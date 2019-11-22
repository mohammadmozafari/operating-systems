// test this program with syscall getpid (11) or getppid (22)

#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int system_call = atoi(argv[1]);
    int number_of_syscall;

    getpid();
    getppid();
    getpid();
    getpid();
    getpid();
    getpid();
    getppid();
    
    number_of_syscall = getCount(system_call);
    printf(1, "system call %d has been invoked %d times\n", system_call, number_of_syscall);
    return 0;
}