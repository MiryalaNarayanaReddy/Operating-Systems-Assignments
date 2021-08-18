#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < 100; i++)
    {
        int t = rand() % 127;
        if (i % 100)
            printf("%c", (char)(t > 32 ? t : ' '));
        else
        {
            printf("\n");
        }
    }
}