#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include "../cd/cd.h"
#include "user.h"

int main()
{
    getcwd(EXECUTABLE_PATH, MAX_PATH_LEN);
    strcpy(CURRENT_DIRECTORY_PATH, "");
    Command command;
    while (true)
    {
        prompt();
        command = Get_Command();
        PerformAction(command);
      
    }

    prompt();
    cd("Shell");
    prompt();
}