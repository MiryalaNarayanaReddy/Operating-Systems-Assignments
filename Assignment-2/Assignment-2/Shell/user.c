#include "user.h"
#include "utils.h"

void prompt()
{
    char buff[1024];
    gethostname(buff, 1024);

    Color_On(__GREEN, BOLD);
    printf("<%s@%s", getlogin(), buff);
    Color_Off();

    printf(":");

    Color_On(__BLUE, BOLD);
    printf("~%s>", CURRENT_DIRECTORY_PATH);
    Color_Off();
}

void Get_Command(char *arguments)
{
    get_string(arguments);
    if (!AreSame(arguments, "\n"))
    {
        push_into_history(arguments);
    }
}

void tokenize(char *source, char *dest)
{
    dest[0] = source[0];
    int i = 1, j = 1;

    while (source[i] != '\0')
    {
        if (dest[j - 1] == ' ' && source[i] == ' ')
        {
            i++;
        }
        else if (dest[j - 1] == ' ' && source[i] == ';')
        {
            dest[j - 1] = source[i];
            i++;
        }
        else if (dest[j - 1] == ';' && source[i] == ' ')
        {
            i++;
        }
        else
        {
            dest[j] = source[i];
            j++;
            i++;
        }
    }
    dest[j] = '\0';
    // printf("Arg = %s->%s\n", arguments, arg);
}

void process_command(char *arguments)
{

    // remove extra spaces;
    char arg[MAX_PATH_LEN];

    tokenize(arguments, arg);

    char *token;
    Command command;
    token = strtok(arg, ";");
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
        if (token[i] == '\0') // a subtle bug ....if you don't check this the cd command with no args may give a seg fault
        {                     // or take the same args as previous cd did.
                              // I had to spend 10-20 minutes runing program again and again to figure it out :(
            if (command == __system_process)
            {
                process(comnd, &token[i]);
            }
            else
            {
                PerformAction(command, &token[i]);
            }
        }
        else
        {
            if (command == __system_process)
            {
                process(comnd, &token[i + 1]);
            }
            else
            {

                PerformAction(command, &token[i + 1]);
            }
        }
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
    else if (AreSame(command, "echo"))
    {
        return __echo;
    }
    else if (AreSame(command, "pwd"))
    {
        return __pwd;
    }
    else if (AreSame(command, "ls"))
    {
        return __ls;
    }
    else if (AreSame(command, "pinfo"))
    {
        return __pinfo;
    }
    else if (AreSame(command, "repeat"))
    {
        return __repeat;
    }
    else if (AreSame(command, "history"))
    {
        return __history;
    }
    else
    {
        return __system_process;
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
    case __clear:
        printf("\e[1;1H\e[2J");
        break;
    case __echo:
        echo(args);
        break;
    case __pwd:
        pwd();
        break;
    case __ls:
        ls(args);
        break;
    case __pinfo:
        pinfo(args);
        break;
    case __repeat:
        repeat(args);
        break;
    case __history:
        history(args);
        break;
    }
}