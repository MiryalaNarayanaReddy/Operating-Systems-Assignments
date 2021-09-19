#include "utils.h"

void init_cd()
{
    getcwd(EXECUTABLE_PATH, MAX_PATH_LEN);

    strcpy(SAVED_PATH, EXECUTABLE_PATH);
    strcpy(CURRENT_DIRECTORY_PATH, "");

    sprintf(USER_HOME_PATH, "/home/%s", getlogin());

    // first time no cd is used
    changed_path = false;
}

void init_process()
{
    parent_pid = getpid();
    number_of_children = 0;
}

void init_signal()
{
    signal(SIGINT, handle_signal);
    signal(SIGTSTP, handle_signal);
    signal(SIGKILL, SIG_DFL);
}

void init_history()
{
    strcpy(history_file_path, EXECUTABLE_PATH);
    strcat(history_file_path, "/history/history.txt");

    FILE *fp = fopen(history_file_path, "r");
    if (fp == NULL)
    {
        Color_On(__RED, !BOLD);
        printf("Failed to access history.txt file\n");
        Color_Off();
    }
    fscanf(fp, "%d", &number_of_lines_in_history);
    int n = number_of_lines_in_history;
    int i = 0;
    get_line(fp, History[i]);
    while (!feof(fp))
    {
        //  printf("%s\n", History[i]);
        i++;
        get_line(fp, History[i]);
    }

    //    printf("%s\n", History[i]);
    fclose(fp);

    //History
}

void init()
{
    init_cd();
    init_process();
    init_signal();
    init_history();
}
