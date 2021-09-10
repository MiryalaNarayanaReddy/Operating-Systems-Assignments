#include "utils.h"

//gets the whole string upto end of line leaving trailing white spaces.
void get_string(char *s)
{
    char ch;
    int i = 0;
    while ((ch = getchar()) == ' ') // to remove spaces in the begining
        ;
    if(ch=='\n'){
        s[0] = '\n';
        s[1]='\0';
        return;
    }
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


bool AreSame(char *a, char *b)
{
    if (strcmp(a, b) == 0)
    {
        return true;
    }
    else
        return false;
}
