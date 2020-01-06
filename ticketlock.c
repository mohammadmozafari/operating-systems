#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "ticketlock.h"

void initTicketLock(struct ticketlock *lock, char *name)
{
    lock->name = name;
    lock->proc = 0;
    lock->next_ticket = 0;
    lock->current_turn = 0;
}

void acquireTicketLock(struct ticketlock *lock)
{
    int myTicket;
    myTicket = fetch_and_add(&lock->next_ticket, 1);
    while (lock->current_turn != myTicket); 
        // giveprioriy(lock->proc);
    lock->cpu = mycpu();
    lock->proc = myproc();
    getcallerpcs(&lock, lock->pcs);
}

void releaseTicketLock(struct ticketlock *lock)
{
    lock->pcs[0] = 0;
    lock->proc = 0;
    lock->cpu = 0;
    lock->current_turn++;
}