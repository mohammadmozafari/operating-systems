from multiprocessing import Process, Lock, Queue
from multiprocessing.sharedctypes import Value, Array
import random as rnd
import os
import time

def info(title):
    print(title)
    print('parent process:', os.getppid())
    print('process id:', os.getpid())
    print("")

def mult(mat, shape):
    result = [[0 for i in range(shape)] for i in range(shape)]
    for i in range(shape):
        for j in range(shape):
            for k in range(shape):
                result[i][j] += mat[i][k] * mat[k][j]
    return result

def mult_mp(mat, shape, row, queue):
    new_row = [0 for i in range(shape)]
    for i in range(shape):
        for j in range(shape):
            new_row[i] += mat[row][j] * mat[j][i]
    queue.put((row, new_row))
    info('row ' + str(row))

def main():
    shape = 200
    procs = 200
    p = []

    mat = [[rnd.randint(1, 10) for i in range(shape)] for i in range(shape)] 
    result = [[0 for i in range(shape)] for i in range(shape)]
    first = time.time()
    
    
    # result = mult(mat, shape)
    queue = Queue()
    p = [Process(target=mult_mp, args=(mat, shape, i, queue)) for i in range(procs)]   
    for q in p:
        q.start()
    for q in p:
        q.join()
        x, y = queue.get()
        result[x] = y

    for i in range(shape):
        for j in range(shape):
            print(result[i][j], end=' ')
        print()
    end = time.time()
    print('time', (end - first))
        
main()