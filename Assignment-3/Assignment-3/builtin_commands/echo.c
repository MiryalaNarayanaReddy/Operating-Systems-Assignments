#include "echo.h"
#include <wait.h>

void echo(char *args)
{
     printf("%s\n",args);

    // int i = 0;
    // while (args[i] != '\0')
    // {
    //     if (args[i] == ' ' && args[i + 1] == '>' && args[i + 2] == ' ')
    //     {
    //         break;
    //     }
    //     i++;
    // }
    // if (args[i] == '\0')
    // {
    //     printf("%s\n", args);
    // }
    // else
    // {
    //     char file_name[20];
    //     strcpy(file_name, &args[i + 2]);
    //     args[i] = '\0';

    //     pid_t chd = fork();
    //     if (chd == 0)
    //     {
    //         redirect_output(file_name);
    //         printf("%s", args);
    //         exit(EXIT_SUCCESS);
    //     }
    //     else if (chd < 0)
    //     {

    //         printf("internal error: failed to fork ..\n");
    //     }
    //     else
    //     {
    //         wait(NULL);
    //     }
    // }
}
