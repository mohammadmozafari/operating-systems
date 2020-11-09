import threading
import time

mut = threading.Lock()
wr = threading.Lock()
rc = 0

def reader():
    global rc
    counter = 0
    while counter < 10:
        mut.acquire()
        if rc == 0:
            wr.acquire()
        rc += 1
        mut.release()
        
        print('reading ...')
        time.sleep(2)
        print('end reading')
        
        mut.acquire()
        rc -= 1
        if rc == 0:
            wr.release()
        mut.release()
        counter += 1


def writer():
    # while True:
    wr.acquire()

    print('writing ...')
    time.sleep(2)
    print('end writing')
    
    wr.release()

def main():
    r1 = threading.Thread(target=reader)
    r2 = threading.Thread(target=reader)
    w1 = threading.Thread(target=writer)

    r1.start()
    w1.start()
    r2.start()


main()
