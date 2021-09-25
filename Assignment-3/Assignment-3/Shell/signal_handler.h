#ifndef __SIGNAL_HANDLER_H__
#define __SIGNAL_HANDLER_H__

#include <signal.h>

void handle_signal(int signal);
void handle_ctrl_c_signal();
void handle_ctrl_z_signal();
void handle_kill_signal();

#endif