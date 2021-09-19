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
    char id[20] ;
    fscanf(fp, "%s", info); // pid
    strcpy(id,info);
    printf("process id     : %s\n", info);
    fscanf(fp, "%s", info); // tcomm
    fscanf(fp, "%s", info); // state
    printf("process status : %s", info);
    int i = 4;
    for (; i <= 8; i++)
    {
        fscanf(fp, "%s", info);
    }
    // printf("\n%s---%s\n",id, info);
    printf("%s\n", (AreSame(info,id)) ? "+" : ""); //prent id is same as 8th column of proc/pid/stat file then it is forground process
    for (; i <= 23; i++)
    {
        fscanf(fp, "%s", info);
    }
    printf("Virtual Memory : %s bytes\n", info);

    fclose(fp);
    info[0]='\0';
    readlink(exe_path, info, MAX_PATH_LEN);
    printf("executable path : %s\n", info);
}