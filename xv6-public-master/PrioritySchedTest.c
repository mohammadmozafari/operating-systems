#include "types.h"
#include "user.h"

struct pr {
    int ct, tt, st, rt, rut;
    int pid;
};

int main()
{
    const int fork_num = 25, class_num = 5;
    int i, j, fid;
	int sum_tt[class_num], sum_wt[class_num], sum_ct[class_num];
    int total_tt = 0, total_wt = 0, total_ct = 0;
    int each_class = fork_num / class_num;
    struct pr *prc[fork_num];

    struct timeVariables *temp;
    int temp_id;
    
    changePolicy(2);
    changePriority(1);
    for (i = 0 ; i < class_num; i++)
    {
        sum_tt[i] = 0;
        sum_wt[i] = 0;
        sum_ct[i] = 0;
    }

    for (i = 0; i < fork_num; i++)
        prc[i] = (struct pr*)malloc(sizeof(struct pr));

    for (i = 0; i < fork_num; i++)
    {  
        fid = fork();
        if (fid == 0)
        {
            changePriority(class_num - i / class_num);
            for (j = 0; j < 500; j++)
                printf(1, "%d: %d\n", (i+1), (j+1));
            exit();
        }
        else if (fid > 0)
        {
            prc[i]->pid = fid;
        }
        
    }

    for (i = 0; i < fork_num; i++)
    {
        temp = (struct timeVariables*)malloc(sizeof(struct timeVariables));
        temp_id = waitForChild(temp);
        if (temp_id == -1) continue;
        for (j = 0; j < fork_num; j++)
        {
            if (prc[j]->pid == temp_id)
            {
                prc[j]->ct = temp->creationTime;
                prc[j]->tt = temp->terminationTime;
                prc[j]->rt = temp->readyTime;
                prc[j]->rut = temp->runningTime;
                prc[j]->st = temp->sleepingTime;
            }
        }
    }

	printf(1, "\n");
    for (i = 0; i < fork_num; i++)
    {
        printf(1, "process %d -> created: %d - terminated: %d - slept: %d - ready: %d - running: %d\n", prc[i]->pid, prc[i]->ct, prc[i]->tt, prc[i]->st, prc[i]->rt, prc[i]->rut);
        printf(1, "T.T: %d, W.T: %d, CBT: %d\n", (prc[i]->tt - prc[i]->ct), (prc[i]->tt - prc[i]->ct - prc[i]->rut), prc[i]->rut);
        printf(1, "====================================================================================\n");
        sum_tt[i / class_num] += prc[i]->tt - prc[i]->ct;
		sum_wt[i / class_num] += prc[i]->tt - prc[i]->ct - prc[i]->rut;
		sum_ct[i / class_num] += prc[i]->rut;
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