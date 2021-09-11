#include "process.h"
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>

void process(char *command, char *args)
{
    // pid_t parent = getpid();
    pid_t pid = fork();
    if (pid == 0)
    {
        char argv[10][MAX_ARGS];

        char *token;
        char *strptr;
        int i = 0;
        token = strtok_r(args, " ", &strptr);
        while (token != NULL)
        {
            strcpy(argv[i], token);
            i++;
            token = strtok_r(NULL, " ", &strptr);
        }
        strcpy(argv[i], "\0");
        execvp(command, argv);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // split args
        wait(NULL);
        // printf("Done\n");
    }
}