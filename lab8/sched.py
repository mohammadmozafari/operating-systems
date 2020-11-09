procs = [[1, 10, 0, 1], [2, 12, 1, 7], [3, 3, 0, 0], [4, 5, 1, 5]]
n = len(procs)
quantum = 3

ticks = 0
i = 0
while ticks < 200:
	
	chosen = None	
	j = i
	while True:
		if (procs[j][1] > 0) and (procs[j][2] == 1) and (procs[j][3] <= ticks):
			chosen = j
			i = j
			break
		j += 1
		j = j % n
		if (j == i):
			break
	
	if chosen == None:
		j = i
		while True:
			if (procs[j][1] > 0) and (procs[j][3] <= ticks):
				chosen = j
				i = j
				break
			j += 1
			j = j % n
			if (j == i):
				break
		
	if chosen == None:
		ticks += 1
		continue
	
	timeslot = min(quantum, procs[chosen][1])
	ticks += timeslot
	procs[chosen][1] -= timeslot
	print('process', (chosen + 1), 'executed for', timeslot, 'clocks', '(ticks=', str(ticks) + ')')

	
