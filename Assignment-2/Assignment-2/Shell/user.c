#include "user.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "../cd/cd.h"
#include <stdlib.h>

void prompt()
{
    char buff[1024];
    gethostname(buff, 1024);
    Color_On(__GREEN);
    Bold(true);
    printf("<%s@%s:~", getlogin(), buff);
    Color_Off();
    Bold(false);
    printf("%s>", CURRENT_DIRECTORY_PATH);
}

void Get_Command(char *arguments)
{
    get_string(arguments);
}

void process_command(char *arguments)
{
    char *token;
    Command command;
    token = strtok(arguments, ";");

    while (token != NULL)
    {
        // printf("t =  %s\n", token);
        int i = 0;
        char comnd[MAX_PATH_LEN];
        while (token[i] != '\0' && token[i] != ' ')
        {
            comnd[i] = token[i];
            i++;
        }
        comnd[i] = '\0';
        command = encode_command(comnd);
        PerformAction(command, &token[i + 1]);

        token = strtok(NULL, ";");
    }
}

Command encode_command(char *command)
{
    if (AreSame(command, "cd"))
    {
        return __cd;
    }
    else if (AreSame(command, "\n"))
    {
        return __new_line;
    }
    else if (AreSame(command, "exit"))
    {
        return __exit;
    }
    else if (AreSame(command, "clear"))
    {
        return __clear;
    }
    else
    {
        return __invalid_command;
    }
}

void PerformAction(Command command, char *args)
{
    switch (command)
    {
    case __cd:
        cd(args);
        break;
    case __new_line:
        break;
    case __exit:
        exit(EXIT_SUCCESS);
        break;
    case __invalid_command:
        Color_On(__RED);
        printf("Invalid command:\n");
        Color_Off();
        printf("no such file or directory\n");
        break;
    case __clear:
        printf("\e[1;1H\e[2J");
        break;
    }
}