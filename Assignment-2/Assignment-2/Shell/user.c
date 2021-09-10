#include "user.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "../cd/cd.h"

//gets the whole string upto end of line leaving trailing white spaces.
void get_string(char *s)
{
    char ch;
    int i = 0;
    while ((ch = getchar()) == ' ') // to remove spaces in the begining
        ;
    do
    {
        s[i++] = ch;
    } while ((ch = getchar()) != '\n');
    while (s[i - 1] == ' ') //to remove the spaces at the end
    {
        i--;
    }
    s[i] = '\0';
}

void clean_input()
{
    char ch;
    while ((ch = getchar()) != '\n')
        ;
}

void Color_On(int color)
{
    printf("\033[231;%dm", color);
}

void Bold(bool state)
{
    if (state)
    {
        printf("\e[1m");
    }
    else
    {
        printf("\e[0m");
    }
}

void Color_Off()
{
    printf("\033[m");
}

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

bool AreSame(char *a, char *b)
{
    if (strcmp(a, b) == 0)
    {
        return true;
    }
    else
        return false;
}

Command Get_Command()
{
    char command[100];
    int i = 0;
    while ((command[i] = getchar())!=' ')
    {
        if (command[i] == '\n')
        {
            break;
        }
        else
        {
            i++;
        }
    }
    command[i]='\0';
    if (AreSame(command, "cd"))
    {
        return __cd;
    }
    else if (AreSame(command, "\n"))
    {
        return __new_line;
    }
    else
    {
        return -1;
    }
}

void PerformAction(Command command)
{
    char input_string[MAX_PATH_LEN];
   

    switch (command)
    {
    case __cd:
        get_string(input_string);
        cd(input_string);
    case __new_line:
        return;
    }
}