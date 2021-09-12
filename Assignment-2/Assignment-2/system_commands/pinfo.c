#include "pinfo.h"

void pinfo(char *pid)
{
    char path[MAX_PATH_LEN];
    char exe_path[MAX_PATH_LEN];

    if (AreSame(pid, ""))
    {
        sprintf(path, "/proc/%d/stat", getpid());
        sprintf(exe_path, "/proc/%d/exe", getpid());
    }
    else
    {
        sprintf(path, "/proc/%s/stat", pid);
        sprintf(exe_path, "/proc/%s/exe", pid);
    }

    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        char temp[MAX_PATH_LEN + 22];
        sprintf(temp, "could not access : %s\n", path);
        perror(path);
        return;
    }
    char info[MAX_PATH_LEN];
    fscanf(fp, "%s", info); // pid
    printf("process id     : %s\n", info);
    fscanf(fp, "%s", info); // command
    fscanf(fp, "%s", info); // state
    printf("process status : %s\n", info);
    for (int i = 1; i <= 22; i++)
    {
        fscanf(fp, "%s", info);
    }
    printf("Virtual Memory : %s\n", info);

    fclose(fp);

    readlink(exe_path, info, MAX_PATH_LEN);
    printf("executable path : %s\n", info);
}