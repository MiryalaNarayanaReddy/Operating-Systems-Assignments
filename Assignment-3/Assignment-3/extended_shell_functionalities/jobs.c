#include "jobs.h"
#include <fcntl.h>
#include <wait.h>

void push_into_jobs(char *p, int pid)
{
    strcpy(jobs[num_jobs].name, p);
    jobs[num_jobs].pid = pid;
    num_jobs++;
}

char pstatus(int pid)
{
    char path[100];
    sprintf(path, "/proc/%d/stat", pid);
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        return 'T';
    }
    char temp[100];
    fscanf(fp, "%s", temp);
    fscanf(fp, "%s", temp);
    fscanf(fp, "%s", temp);
    fclose(fp);
    return (temp[0] == 'S' ? 'R' : temp[0]);
}

char *expand_status(char ch)
{
    switch (ch)
    {
    case 'S':
        return "Sleeping";
        break; // no need :P
    case 'R':
        return "Running";
        break;
    case 'T':
        return "Stopped";
        break;
    case 'Z':
        return "Zombie";
        break;
    default:
        return "undefined";
        break;
    }
}

void list_jobs(char *args)
{
    char st;
    FILE *fp = fopen("temp_XXXX.txt", "w");
    fclose(fp);
    fp = fopen("temp_XXXX.txt", "a");

    if (AreSame(args, ""))
        for (int i = 0; i < num_jobs; i++)
        {
            st = pstatus(jobs[i].pid);
            fprintf(fp, "[%d] %s %s [ %d ]\n", i + 1, expand_status(st), jobs[i].name, jobs[i].pid);
        }
    else if (AreSame(args, "-r"))
        for (int i = 0; i < num_jobs; i++)
        {
            st = pstatus(jobs[i].pid);
            if (st == 'R')
                fprintf(fp, "[%d] %s %s [ %d ]\n", i + 1, expand_status(st), jobs[i].name, jobs[i].pid);
        }
    else if (AreSame(args, "-s"))
        for (int i = 0; i < num_jobs; i++)
        {
            st = pstatus(jobs[i].pid);
            if (st == 'T')
                fprintf(fp, "[%d] %s %s [ %d ]\n", i + 1, expand_status(st), jobs[i].name, jobs[i].pid);
        }
    fclose(fp);
    int s;
    int pid = fork();

    if (pid == 0)
    {
        // dup2(STDOUT_FILENO,STDOUT_FILENO);
        execl("/bin/sort", "sort", "-k3,3", "-k5,5n", "temp_XXXX.txt", NULL);
        exit(0);
    }
    else if (pid < 0)
    {
        perror("Error forking for sort");
    }
    else
    {
        waitpid(pid, &s, 0);
    }

    remove("temp_XXXX.txt");
}

void kill_job(char *args)
{
    int id, signal;
    char *token;
    char *strptr;
    token = strtok_r(args, " ", &strptr);
    if (token != NULL)
    {
        id = string_to_int(token);
        if (id == -1)
        {
            perror("job number is not a number\n");
            return;
        }
    }
    token = strtok_r(NULL, " ", &strptr);
    if (token != NULL)
    {
        signal = string_to_int(token);
        if (signal == -1)
        {
            perror("signal is not a number\n");
            return;
        }
    }
    // printf("%d %d\n",id,signal);
    if (id > num_jobs)
    {
        perror("Invalid pid or process is not created by this shell \n");
        return;
    }
    kill(jobs[id - 1].pid, signal);
}

void fg(char *args)
{
    // background to foreground
    int id = string_to_int(args);
    if (id == -1)
    {
        perror("job number is not a number\n");
        return;
    }
    // printf("%d\n", id);
    id--; // since ids are printed by adding 1
    if (id >= num_jobs || id < 0)
    {
        perror("Invalid job number or process is not created by this shell \n");
        return;
    }
    // main part

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, jobs[id].pid); //set foreground process grp
    kill(jobs[id].pid, SIGCONT);

    int st;
    current_fg = jobs[id];
    waitpid(jobs[id].pid, &st, WUNTRACED);

    tcsetpgrp(0, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}

void bg(char *args)
{
    // stopped background to running
    int id = string_to_int(args);
    if (id == -1)
    {
        perror("Job number is not a number\n");
        return;
    }
    id--;
    // printf("%d\n", id);
    if (id >= num_jobs || id < 0)
    {
        perror("Invalid job number or process is not created by this shell \n");
        return;
    }
    // main part

    char *temp[MAX_ARGS];
    char name[1000];
    strcpy(name, jobs[id].name);
    int i = 0;
    char *token;
    char *strptr;
    token = strtok_r(name, " ", &strptr);
    while (token != NULL)
    {
        temp[i] = &token[0];
        i++;
        token = strtok_r(NULL, " ", &strptr);
    }
    temp[i] = NULL;
    pid_t ch_pid = fork();
    if (ch_pid == 0)
    {
        if (execvp(temp[0], temp) == -1)
        {
            Color_On(__RED, BOLD);
            printf("Command invalid :(\n");
            Color_Off();
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else if (ch_pid < 0)
    {
        Color_On(__YELLOW, BOLD);
        printf("Forking failed \n");
        Color_Off();
    }
    else
    {
        // push_into_jobs(temp_process_name, child_pid);
        jobs[id].pid = ch_pid;
        printf("[%d] pid = %d\n", id + 1, ch_pid);
        setpgid(ch_pid, 0);
        tcsetpgrp(0, getpgrp());
    }
}
