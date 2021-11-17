#include "user.h"


void Bold(bool status)
{
    if (status)
    {

        printf("\e[1m");
    }
    else
    {
        printf("\e[0m");
    }
}

void Color_On(int color, bool bold)
{
    if (bold)
    {
        printf("\033[231;%dm\e[1m", color);
    }
    else
    {
        printf("\033[231;%dm", color);
    }
}

void Color_Off()
{
    printf("\033[m");
}