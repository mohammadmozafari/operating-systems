import threading as th
import time

class Write(th.Thread):
    def __init__(self, text, output):
        th.Thread.__init__(self)
        self.text = text
        self.out = output
    
    def run(self):
        with open(self.out, 'a') as f:
            f.write(self.text)
        print('writing done')
        time.sleep(2)

def main():
    message = input('write something:')
    t1 = Write(message, 'output_file.txt')
    t1.start()

    print('waiting for thread to finish')
    print('1+2= ', 1 + 2)
    t1.join()

if __name__ == '__main__':
    main()