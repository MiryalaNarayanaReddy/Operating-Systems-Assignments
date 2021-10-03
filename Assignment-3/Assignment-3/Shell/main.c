#include "utils.h"
#include "init.h"

int main()
{
    char argument[MAX_ARGS];
    init();
    
    while (true)
    {
        prompt();
        Get_Command(argument);
        // process_command(argument);
        check_for_pipes(argument);
    }
}
