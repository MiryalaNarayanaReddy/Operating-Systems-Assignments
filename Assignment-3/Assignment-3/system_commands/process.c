#include "process.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void process(char *command, char *args)
{
    char *argv[MAX_ARGS];
    int num_args = parse_cmd(command, args, argv);
    if (AreSame(argv[num_args - 1], "&"))
    {
        argv[num_args - 1] = NULL;
        background_process(argv);
    }
    else
    {
        forground_process(argv);
    }
    printf("\r"); // just to remove the first prompt being printed by the signal interrupt.
}

int parse_cmd(char *command, char *args, char *argv[10])
{
    // printf("%s\n%s\n", command, args);
    argv[0] = &command[0];
    char *token;
    char *strptr;
    int i = 1;
    token = strtok_r(args, " ", &strptr);
    while (token != NULL)
    {
        argv[i] = &token[0];
        i++;
        token = strtok_r(NULL, " ", &strptr);
    }
    argv[i] = NULL;
    return i;
}

void forground_process(char **argv)
{
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        if (execvp(argv[0], argv) == -1)
        {
            Color_On(__RED, BOLD);
            printf("Command invalid :(\n");
            Color_Off();
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else if (child_pid < 0)
    {
        Color_On(__YELLOW, BOLD);
        printf("Forking failed\n");
        Color_Off();
    }
    else
    {
        signal(SIGCHLD, process_status);
        wait(NULL);
    }
}

void background_process(char **argv)
{
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        if (execvp(argv[0], argv) == -1)
        {
            Color_On(__RED, BOLD);
            printf("Command invalid :(\n");
            Color_Off();
            exit(EXIT_FAILURE); // not valid and verified
        }
        exit(EXIT_SUCCESS);
    }
    else if (child_pid < 0)
    {
        Color_On(__YELLOW, BOLD);
        printf("Forking failed \n");
        Color_Off();
    }
    else
    {
        setpgid(child_pid, getpgid(parent_pid)); // set the child process group id to parent process group id
        // setting this will help us select options in the waitpid function.
        child_processes[number_of_children] = child_pid;
        strcpy(child_process_name[number_of_children], argv[0]);
        number_of_children++;
        signal(SIGCHLD, process_status); // child exit
        printf("pid = %d\n", child_pid);
    }
}

void process_status()
{
    pid_t result;
    int status;
    result = waitpid(0, &status, 0); // returns 0 if child is not already dead.
    if (result >= 0)
    {
        //check all child process in the list
        for (int i = 0; i < number_of_children; i++)
        {
            if (child_processes[i] == result) // our child process is in the list ...
            {
                if (child_processes[i] != 0) // check child process id
                {
                    if (WIFEXITED(status) & WEXITSTATUS(status) == EXIT_SUCCESS) // WIFEXITED --> is exit normal  && WEXITSTATUS ---> did it exit with exit code 0.
                    {
                        Color_On(__PINK, !BOLD);
                        printf("\n\" %s \" with pid = %d exited normally\n", child_process_name[i], child_processes[i]);
                        Color_Off();
                        printf("continue with your command or press enter to continue...\n");
                        // prompt();
                        // fflush(stdin);
                        return;
                    }
                    else // if (WIFSIGNALED(status)) ---> this is always true
                    {
                        Color_On(__PINK, !BOLD);
                        printf("\n\" %s \" with pid = %d exited abnormally\n", child_process_name[i], child_processes[i]);
                        Color_Off();
                        printf("continue with your command or press enter to continue...\n");
                        // prompt();
                        // fflush(stdout);
                        return;
                    }
                }
            }
            child_processes[i] = 0; // its dead or exited
            // number_of_children--;   // decrease number of children by one.
        }
    }
    else
        return;
}
