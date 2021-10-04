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
    strcpy(parent_process.name, "./a.out");
    parent_process.pid = getpid();
    num_jobs = 0;
    current_fg = parent_process;
}

void init_signal()
{
    signal(SIGINT, handle_signal);
    signal(SIGTSTP, handle_signal);
    signal(SIGKILL, SIG_DFL);
    Handel_background_process_exit();
}

void init_history()
{
    strcpy(history_file_path, EXECUTABLE_PATH);
    strcat(history_file_path, "/history/history.txt");

    FILE *fp = fopen(history_file_path, "r");
    char temp[MAX_PATH_LEN];
    int i = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s", temp);
        i++;
    }
    number_of_lines_in_history = i;
}

void init()
{
    init_cd();
    init_process();
    init_signal();
    init_history();
}
