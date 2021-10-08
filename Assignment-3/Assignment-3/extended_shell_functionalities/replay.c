#include "replay.h"
#include <time.h>

// replay -command echo "hello" -interval 3 -period 6
// perror("usage: replay -command <command> -interval <interval> -period <period>\n");
// replay -command echo "hello world" -interval 3 -period 10

void replay(char *str)
{
    char command[MAX_PATH_LEN];
    command[0] = '\0';
    char temp[MAX_PATH_LEN];
    char period[10];
    char interval[10];
    // -command  -> 8
    // -interval -> 9
    // -period   -> 7

    int i = 0, j = 0;
    while (str[i] != ' ')
    {
        temp[j++] = str[i++];
    }
    temp[j] = '\0';
    if (!AreSame(temp, "-command"))
    {
        printf("usage: replay -command <command> -interval <interval> -period <period>\nHint: look at the -command\n");
        return;
    }
    else
    {
        int k = strlen(str) - 1;
        int c = 0;
        while (str[k] != ' ')
        {
            k--;
        }
        strcpy(period, &str[k + 1]);
        str[k] = '\0';
        k--;

        while (str[k] != ' ')
        {
            k--;
        }
        strcpy(temp, &str[k + 1]);
        str[k] = '\0';
        k--;
        if (!AreSame(temp, "-period"))
        {
            printf("usage: replay -command <command> -interval <interval> -period <period>\nHint: look at -period\n");
            return;
        }
        while (str[k] != ' ')
        {
            k--;
        }
        strcpy(interval, &str[k + 1]);
        str[k] = '\0';
        k--;
        while (str[k] != ' ')
        {
            k--;
        }
        strcpy(temp, &str[k + 1]);
        str[k] = '\0';
        k--;

        if (!AreSame(temp, "-interval"))
        {
            printf("usage: replay -command <command> -interval <interval> -period <period>\nHint: look at -interval\n");
            return;
        }
    }

    strcpy(command, &str[j + 1]);

    // printf("-%s-%s-%s-\n", command, interval, period);
    int interval_t = string_to_int(interval);
    int period_t = string_to_int(period);

    // printf("%s %d %d \n", temp, interval_t, period_t);

    char temp2[MAX_PATH_LEN];

    time_t present = time(NULL);
    time_t future = present + period_t;

    while (present < future)
    {
        present = time(NULL);
        if (interval_t <= future - present)
        {
            sleep(interval_t);
            present += interval_t;
        }
        else
        {
            sleep(future - present);
            present = future;
            break;
        }
        strcpy(temp2, command);
        process_command(temp2);
    }

    return;
}
