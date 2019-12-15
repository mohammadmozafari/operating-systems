import threading
import time

lock = threading.Lock()
def timer(name, decay):
    lock.acquire()
    counter = 4
    while (counter > 0):
        time.sleep(decay)
        print('{0} : {1}'.format(name, time.ctime(time.time())))
        counter -= 1
    lock.release()

def main():
    t1 = threading.Thread(target=timer, args=('t1', 1))
    t2 = threading.Thread(target=timer, args=('t2', 1))
    print('t1 is starting')
    t1.start()
    print('t2 is starting')
    t2.start()
    
if __name__ == '__main__':
    main()