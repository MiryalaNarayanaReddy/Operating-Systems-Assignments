#include "signal_handler.h"
#include "utils.h"

void handel_signal(int signal)
{
    switch (signal)
    {
    case SIGINT:
        handel_ctrl_c_signal();
        break;
    case SIGTSTP:
        handel_ctrl_z_signal();
        break;
    }
}

void handel_ctrl_c_signal()
{
    // pid_t pid = getpid();
    // kill(pid, SIGSTOP);
    printf("\n");
    prompt();
    fflush(stdout);
    return;
}

void handel_ctrl_z_signal()
{
    printf("\n");
    prompt();
    fflush(stdout);
    return;
}
