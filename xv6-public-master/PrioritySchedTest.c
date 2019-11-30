#include "types.h"
#include "user.h"

int main()
{
    const int fork_num = 25, class_num = 5;
    int i, j;
    struct timeVariables *t[fork_num];
    int childrenId[fork_num];
    int ct, tt, st, rt, rut;
	int sum_tt[class_num], sum_wt[class_num], sum_ct[class_num];
    int total_tt = 0, total_wt = 0, total_ct = 0;
    int each_class = fork_num / class_num;
    
    changePolicy(2);
    for (i = 0 ; i < class_num; i++)
    {
        sum_tt[i] = 0;
        sum_wt[i] = 0;
        sum_ct[i] = 0;
    }

    for (i = 0; i < fork_num; i++)
        t[i] = (struct timeVariables *)malloc(sizeof(struct timeVariables));

    for (i = 0; i < fork_num; i++)
    {
        if (fork() == 0)
        {
            changePriority(i / class_num);
            for (j = 0; j < 1000; j++)
                printf(1, "%d: %d\n", (i+1), (j+1));
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
			
            sum_tt[i / class_num] += tt - ct;
			sum_wt[i / class_num] += tt - ct - rut;
			sum_ct[i / class_num] += rut;
        }
    }
	
    for (i = 0; i < class_num; i++)
    {
        printf(1, "\nGroup With Priority : %d\n", class_num - i);
        printf(1, "Avg T.T: %d, Avg W.T: %d, Avg CBT: %d\n", sum_tt[i] / each_class, sum_wt[i] / each_class, sum_ct[i] / each_class);
	    printf(1, "=========================================\n");
        total_tt += sum_tt[i];
        total_wt += sum_wt[i];
        total_ct += sum_ct[i];
    }

    printf(1, "\nALL\n");
    printf(1, "Avg T.T: %d, Avg W.T: %d, Avg CBT: %d\n", total_tt / fork_num, total_wt / fork_num, total_ct / fork_num);
	printf(1, "=========================================\n");
	return 0;
}