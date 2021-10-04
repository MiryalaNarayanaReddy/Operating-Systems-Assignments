#include "signal_handler.h"
#include "utils.h"

// global signal handlers.
void handle_signal(int signal)
{
    switch (signal)
    {
    case SIGINT:
        handle_ctrl_c_signal();
        break;
    case SIGTSTP:
        handle_ctrl_z_signal();
        break;
    }
}

void handle_ctrl_c_signal()
{
    // pid_t pid = getpid();
    // kill(pid, SIGSTOP);
    printf("\n");
    prompt();
    fflush(stdout);
    return;
}

void handle_ctrl_z_signal()
{
    // if (current_fg.pid != parent_process.pid)
    // {
    //     printf("in different process");
    //     push_into_jobs(current_fg.name, current_fg.pid);
    //     printf("[ %d ] pid = %d   %s", num_jobs - 1, current_fg.pid, current_fg.name);
    // }
    printf("\n");
    prompt();
    fflush(stdout);
    return;
}
