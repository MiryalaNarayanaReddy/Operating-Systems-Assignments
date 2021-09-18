#include "signal_handler.h"
#include "utils.h"

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
    printf("\n");
    prompt();
    fflush(stdout);
    return;
}
