import socket as sc
from _thread import start_new_thread
import threading

lock = threading.Lock()
def threaded(c):
    # lock.acquire()
    while True:
        data = c.recv(1024)
        if not data:
            print('bye')
            break
        data = data[::-1]
        c.send(data)
    s.close()
    # lock.release();

host = ''
port = 12354
s = sc.socket(sc.AF_INET, sc.SOCK_STREAM)

s.bind((host, port))
print('socket binded')

s.listen(5)
print('socket listening')

while True:
    con, add = s.accept()
    start_new_thread(threaded, (con, ))

s.close()