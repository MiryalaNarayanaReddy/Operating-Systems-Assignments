#ifndef __SIGNAL_HANDLER_H__
#define __SIGNAL_HANDLER_H__

#include <signal.h>

void handel_signal(int signal);
void handel_ctrl_c_signal();
void handel_ctrl_z_signal();

#endif