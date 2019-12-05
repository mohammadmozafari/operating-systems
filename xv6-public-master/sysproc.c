#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

// Written By 9631069
int
sys_getppid(void)
{
  return myproc()->parent->pid;
}

// Written By 9631069
int
sys_getChildren(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return children_number(pid);
}

// Written By 9631069
int
sys_getCount(void)
{
  int sysid;
  if(argint(0, &sysid) < 0)
    return -1;
  return myproc()->syscall_times[sysid];
}

// changes the priority of the current process. the new priority must be in range (1, 5)
int
sys_changePriority(void)
{
  int pr;
  if(argint(0, &pr) < 0)
    return -1;
  if (pr >= 5 || pr < 1)
    return -1;
  myproc()->priority = pr;
  return 1;
}

// changes the xv6 policy for cpu scheduling. legal values are 0, 1, 2
int
sys_changePolicy(void)
{
  int pol;
  if(argint(0, &pol) < 0)
    return -1;
  if (pol > 2 || pol < 0)
    return -1;
  policy = pol;
  return 1;
}

// waits until a child terminates and get the child's time variables in a struct
int
sys_waitForChild(void)
{
  struct timeVariables *tv;
  if (argptr(0, (void*)&tv, sizeof(*tv)) < 0)
    return -1;
  return waitForChild(tv);
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
