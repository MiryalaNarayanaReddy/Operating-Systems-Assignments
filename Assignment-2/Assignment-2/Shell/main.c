#include "utils.h"

void init()
{
    getcwd(EXECUTABLE_PATH, MAX_PATH_LEN);

    strcpy(SAVED_PATH, EXECUTABLE_PATH);
    strcpy(CURRENT_DIRECTORY_PATH, "");

    sprintf(USER_HOME_PATH, "/home/%s", getlogin());

    changed_path = false;
}

int main()
{
    init();
    Command command;
    char argument[MAX_ARGS];

    while (true)
    {
        prompt();
        Get_Command(argument);
        process_command(argument);
    }
}
