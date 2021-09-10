#include "utils.h"
#include "../cd/cd.h"
#include "user.h"

#define MAX_ARGS 100
int main()
{
    getcwd(EXECUTABLE_PATH, MAX_PATH_LEN);
    strcpy(CURRENT_DIRECTORY_PATH, "");
    Command command;
    char argument[MAX_ARGS];

    while (true)
    {
        prompt();
        Get_Command(argument);
        // printf("%s\n",argument);
        process_command(argument);
    }
}