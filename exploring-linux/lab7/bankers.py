import threading
import time
import copy

n = 5
m = 3
available_res = [3,3,2]
max_request= [[7,5,3],
			[3,2,2],
			[9,0,2],
			[2,2,2],
			[4,3,3]]
allocated_res = [[0,1,1],
				[2,0,0],
				[3,0,2],
				[2,1,1],
				[0,0,2]]

need = copy.deepcopy(max_request)
for i in range(n):
	for j in range(m):
		need[i][j] -= allocated_res[i][j]
	

def is_safe(need, available, allocated):
	
	sequence = []
	finish = [False for i in range(n)]

	while True:
		exist = False
		for i in range(5):
			flag1 = True
			for j in range(m):
				if available [j] < need[i][j]:
					flag1 = False
					break
			if finish[i] == False and flag1:
				exist = True
				finish[i] = True
				for j in range(m):
					available[j] = available[j] + allocated[i][j]
				sequence.append(i)
		if not exist:
			break	
		flag2 = True
		for i in range(n):
			if finish[i ]== False:
				flag2 = False
				break
		if flag2:
			break
	
	flag2 = True
	for i in range(n):
		if finish[i] == False:
			flag2 = False
			break

	if flag2:
		return sequence
	else:
		return False

lock = threading.Lock()
def func(i):
	global available_res
	global max_request
	global allocated_res
	global need

	not_used = True
	while not_used:

		req = copy.deepcopy(need[i])
		check = True
		for j in range(m):
			if req[j] > available_res[j]:
				check = False
		
		if check:
			temp_need = copy.deepcopy(need)
			temp_avai = copy.deepcopy(available_res)
			temp_alloc = copy.deepcopy(allocated_res)

			for j in range(m):
				temp_avai[j] -= req[j]
				temp_alloc[i][j] += req[j]
				temp_need[i][j] -= req[j]

			safe = is_safe(temp_need, temp_avai, temp_alloc)

			if safe:
				lock.acquire()
				not_used = False
				for j in range(m):
					available_res[j] -= req[j]
					allocated_res[i][j] += req[j]
					need[i][j] -= req[j]
				lock.release()

				print('allocated to ' + str(i))
				time.sleep(2)

				lock.acquire()
				for j in range(m):
					available_res[j] += allocated_res[i][j]
					allocated_res[i][j] = 0 
					need[i][j] = 0
				lock.release()


def main():
	t1 = threading.Thread(target=func, args=(0, ))
	t2 = threading.Thread(target=func, args=(1, ))
	t3 = threading.Thread(target=func, args=(2, ))
	t4 = threading.Thread(target=func, args=(3, ))
	t5 = threading.Thread(target=func, args=(4, ))

	t1.start()
	t2.start()
	t3.start()
	t4.start()
	t5.start()

main()
