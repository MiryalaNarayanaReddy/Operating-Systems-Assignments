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

void init()
{
    init_cd();
    init_process();
    init_signal();
}
