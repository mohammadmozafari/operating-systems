import threading
import time
import random

lock1 = threading.Lock()
# 0 : hungry - 1 : thinking - 2 : eating
state = [1, 1, 1, 1, 1]
ph = [threading.Lock(), threading.Lock(), threading.Lock(), threading.Lock(), threading.Lock()]
ph[0].acquire()
ph[1].acquire()
ph[2].acquire()
ph[3].acquire()
ph[4].acquire()

def philosopher(i):
    while True:
        print('ph %d is thinking' % i) 
        take_forks(i)
        print('ph %d is eating' %i)
        time.sleep(random.randint(0, 5))
        print('ph %d done eating' %i)
        put_down_forks(i)

def take_forks(i):
    lock1.acquire()
    state[i] = 0
    test(i)
    lock1.release()
    ph[i].acquire()

def put_down_forks(i):
    lock1.acquire()
    state[i] = 1
    test((i-1) % 5)
    test((i+1) % 5)
    lock1.release()

def test(i):
    if (state[i]==0 and state[(i-1)%5] != 2 and state[(i+1) % 5] != 2):
        state[i] = 2
        ph[i].release()

def main():
    p0 = threading.Thread(target=philosopher, args=(0, ))
    p1 = threading.Thread(target=philosopher, args=(1, ))
    p2 = threading.Thread(target=philosopher, args=(2, ))
    p3 = threading.Thread(target=philosopher, args=(3, ))
    p4 = threading.Thread(target=philosopher, args=(4, ))

    p0.start()
    p1.start()
    p2.start()
    p3.start()
    p4.start()

main()



