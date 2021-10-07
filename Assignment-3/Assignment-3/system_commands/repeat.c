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
    while (command[i] != ' ' && command[i] != '\0')
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

    int n = string_to_int(n_times);
    // printf("-%s-\n", n_times);
    if (n == -1)
    {
        Color_On(__RED, BOLD);
        printf("second argument for repeat is not a number...\n ");
        Color_Off();
        return;
    }

    if (command[i] == '\0')
    {
        Color_On(__YELLOW, BOLD);
        printf("sorry...cann't repeat nothing %d times :( \n", n);
        Color_Off();
        return;
    }

    for (int k = 0; k < n; k++)
    {
        process_command(&command[i]);
    }
}

int string_to_int(char *str)
{
    int n = 0;
    int len = strlen(str);
    //   printf("%d\n",len);
    for (int i = len - 1; i >= 0; i--)
    {
        // printf("%c\n",str[i]);
        if (str[i] >= '0' && str[i] <= '9')
        {
            n *= 10;
            n += str[i] - '0';
        }
        else
        {
            return -1;
        }
    }
    return n;
}