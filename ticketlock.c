#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "ticketlock.h"

/* initialize a ticket lock with a name */
void init_lock(struct ticketlock *lock, char *name)
{
    lock->name = name;
    lock->next_ticket = 0;
    lock->current_turn = 0;
}

/* acquire the ticket lock */
void acquire_lock(struct ticketlock *lock)
{
    int myTicket = fetch_and_add(&lock->next_ticket, 1);
    while (lock->current_turn != myTicket)
        ticket_sleep(lock);
    getcallerpcs(&lock, lock->pcs);
}

/* release the ticketlock */
void release_lock(struct ticketlock *lock)
{
    fetch_and_add(&lock->current_turn, 1);
    wakeup(lock);
}