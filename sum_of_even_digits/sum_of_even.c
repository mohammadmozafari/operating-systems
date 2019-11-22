#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void even_sum(char* result, char* str_mum);


int main()
{
    char *str = "1256664876886345212", result[100];
    even_sum(result, str);
    printf("%s\n", result);
}

// int main()
// {
//     pid_t pid;
//     int pipe_dir1[2], pipe_dir2[2];
    
//     // create pipes and check if any of them failed then exit the program.
//     if (pipe(pipe_dir1) == -1)
//     {
//         printf("Pipe creation failed.");
//         return 1;
//     }
//     if (pipe(pipe_dir2) == -1)
//     {
//         printf("Pipe creation failed.");
//         return 1;
//     }

//     // creates a child process
//     pid = fork();
    
//     if (pid < 0)
//     {
//         printf("Failed to fork the process\n");
//     }
//     else if (pid > 0)
//     {
//         char input[100];
//         printf("(P) Begin parent process\n");
//         printf("(P) Enter a number : ");
//         scanf("%s", input);

//         close(pipe_dir1[0]);     // close reading end of pipe 1
//         write(pipe_dir1[1], input, strlen(input) + 1);
//         close(pipe_dir1[1]);

//         printf("(P) End parent process\n");

//         wait(NULL);
//     }
//     else
//     {
//         int i, x;
//         char pipe_input[100];
//         char pipe_output[100] = "The sum of even digits in the input number:";
//         char sum[100];

//         close(pipe_dir1[1]);
//         read(pipe_dir1[0], pipe_input, 100);

//         printf("(C) %s : %d\n", pipe_input, (int)strlen(pipe_input));
//         sum = even_sum(atoi(pipe_input));
//         x = strlen(pipe_output);
//         for (i = 0; i < (int)strlen(pipe_input); i++)
//             pipe_output[x + i] = pipe_input[i]
//         close(pipe_dir1[0]);

//         printf("(C) End child process\n");
//     }

//     return 0;
// }

void even_sum(char* result, char* str_num)
{
    const int BASE = 48;
    int sum = 0, x, i;

    for (i = 0; i < strlen(str_num); i++)
    {
        x = (int)str_num[i] - BASE;
        if (x % 2 == 0)
            sum += x;
    }
    sprintf(result, "%d", sum);
}