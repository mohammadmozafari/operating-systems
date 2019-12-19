#include "types.h"
#include "user.h"

int main()
{
    const int fork_num = 10;
    int i, j;
    struct timeVariables *t[fork_num];
    int childrenId[fork_num];
    int ct, tt, st, rt, rut;
	int sum_tt = 0, sum_wt = 0, sum_ct = 0;
	int avg_tt, avg_wt, avg_ct;

	changePolicy(1);

    for (i = 0; i < fork_num; i++)
        t[i] = (struct timeVariables *)malloc(sizeof(struct timeVariables));

    for (i = 0; i < fork_num; i++)
    {
        if (fork() == 0)
        {
            printf(1, "process %d is created\n", getpid());
            sleep(100);                                         // wait until all processes are built
            for (j = 0; j < 1000; j++)
                printf(1, "%d: %d\n", getpid(), (j+1));
            exit();
        }
    }
    for (i = 0; i < fork_num; i++)
        childrenId[i] = waitForChild(t[i]);

	printf(1, "\n");
    for (i = 0; i < fork_num; i++)
    {
        if (childrenId[i] != -1)
        {
            ct = t[i]->creationTime;
            tt = t[i]->terminationTime;
            st = t[i]->sleepingTime;
            rt = t[i]->readyTime;
            rut = t[i]->runningTime;
            printf(1, "process %d -> created: %d - terminated: %d - slept: %d - ready: %d - running: %d\n", childrenId[i], ct, tt, st, rt, rut);
            printf(1, "T.T: %d, W.T: %d, CBT: %d\n", (tt - ct), (tt - ct - rut), rut);
            printf(1, "====================================================================================\n");
			sum_tt += tt - ct;
			sum_wt += tt - ct - rut;
			sum_ct += rut;
        }
    }
	avg_tt = sum_tt / fork_num;
	avg_wt = sum_wt / fork_num;
	avg_ct = sum_ct / fork_num;
	printf(1, "\nAvg T.T: %d, Avg W.T: %d, Avg CBT: %d\n", avg_tt, avg_wt, avg_ct);
	printf(1, "=========================================\n");

	return 0;
}