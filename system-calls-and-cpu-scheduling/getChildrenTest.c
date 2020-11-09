#include "types.h"
#include "user.h"

int main()
{
    int ppid;
    int f1 = fork(); 
    int f2 = fork(); 

    if (f1 > 0 && f2 > 0) 
    {
        sleep(10); 
        ppid = getppid();
        printf(1, "pid:%d,ppid:%d,parent's children:%d\n", getpid(), ppid, getChildren(ppid)); 

        wait();
        wait();
    } 
    else if (f1 == 0 && f2 > 0) 
    {
        sleep(30);
        ppid = getppid();
        printf(1, "pid:%d,ppid:%d,parent's children:%d\n", getpid(), ppid, getChildren(ppid));

        wait(); 
    } 
    else if (f1 > 0 && f2 == 0) 
    { 
        sleep(60);
        ppid = getppid();
        printf(1, "pid:%d,ppid:%d,parent's children:%d\n", getpid(), ppid, getChildren(ppid)); 
    } 
    else { 
        sleep(100);
        ppid = getppid();
        printf(1, "pid:%d,ppid:%d,parent's children:%d\n", getpid(), ppid, getChildren(ppid)); 
    } 
  
    return 0;
}