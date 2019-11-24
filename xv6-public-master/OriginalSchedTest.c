#include "types.h"
#include "user.h"

int main()
{
    const int fork_num = 2;
    int fid[fork_num], i;
    int root = 1;
    struct timeVariables *t[fork_num];
    int childrenId[fork_num];
    int ct, tt, st, rt, rut;

    for (i = 0; i < fork_num; i++)
        t[i] = (struct timeVariables *)malloc(sizeof(struct timeVariables));

    for (i = 0; i < fork_num; i++)
    {
        fid[i] = fork();
        if (fid[i] < 0)
            return 1;
    }

    for (i = 0; i < 10; i++)
        printf(1, "%d: %d\n", getpid(), (i+1));

    for (i = 0; i < fork_num; i++)
    {
        if (fid[i] == 0)
        {
            root = 0;
            break;
        }
    }
    if (root == 1)
    {
        for (i = 0; i < fork_num; i++)
        {
            childrenId[i] = waitForChild(t[i]);
        }

        for (i = 0; i < fork_num; i++)
        {
            if (childrenId[i] != 0)
            {
                ct = t[i]->creationTime;
                tt = t[i]->terminationTime;
                st = t[i]->sleepingTime;
                rt = t[i]->readyTime;
                rut = t[i]->runningTime;
                printf(1, "%d : %d %d %d %d %d\n", childrenId[i], ct, tt, st, rt, rut);
                printf(1, "T.T: %d, W.T: %d, CBT: %d\n", (tt - ct), (tt - ct - rut), rut);
                printf(1, "=========================\n");
            }
        }
    }

}