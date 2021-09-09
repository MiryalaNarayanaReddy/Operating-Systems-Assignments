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

void prompt()
{
    char buff[1024];
    gethostname(buff, 1024);
    printf("<%s@%s:~", getlogin(), buff);
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
    scanf("%s", command);
    if (AreSame(command, "cd"))
    {
        return __cd;
    }
}

void PerformAction(Command command)
{
    char input_string[MAX_PATH_LEN];
    get_string(input_string);

    switch (command)
    {
    case __cd:
        cd(input_string);
    }
}