#include "repeat.h"

void repeat(char *command)
{
    if (AreSame(command, ""))
    {
        printf("sorry...can repeat empty times :( \n");
        return;
    }
    char n_times[10];

    int i = 0, j = 0;
    while (command[i] == ' ')
    {
        i++;
    }
    while (command[i] != ' ')
    {
        n_times[j] = command[i];
        j++;
        i++;
    }
    n_times[j] = '\0';
    while (command[i] == ' ')
    {
        i++;
    }

    int n = 0;
    n = atoi(n_times);
    char temp[11];
    sprintf(temp, "%d", n);
    printf("-%s-\n-%s-\n", temp, n_times);
    if (!AreSame(temp, n_times))
    {
        Color_On(__RED, BOLD);
        printf("second argument for repeat is not a number...\n ");
        Color_Off();
        return;
    }

    if (command[i] == '\0')
    {
        Color_On(__YELLOW, !BOLD);
        printf("sorry...can repeat nothing %d times :( \n", n);
        Color_Off();
        return;
    }

    for (int k = 0; k < n; k++)
    {
        process_command(&command[i]);
    }
}
