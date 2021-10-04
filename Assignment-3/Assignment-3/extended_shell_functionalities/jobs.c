#include "jobs.h"
#include <fcntl.h>
#include <wait.h>

void push_into_jobs(char *p, int pid)
{
    strcpy(jobs[num_jobs].name, p);
    jobs[num_jobs].pid = pid;
    process_no = num_jobs;
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
    return temp[0];
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
    printf("%d\n", id);
    if (id > num_jobs)
    {
        perror("Invalid job number or process is not created by this shell \n");
        return;
    }
    // pending;
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
    printf("%d\n", id);
    kill(jobs[id].pid, SIGTTIN);
    kill(jobs[id].pid, SIGCONT);
}
