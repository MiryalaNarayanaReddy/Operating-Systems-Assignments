#include "replay.h"
#include <time.h>
// replay -command echo "hello" -interval 2 -period 6
void replay(char *command)
{
    char temp[100];
    char period[10];
    char interval[10];
    char *token;
    char *strptr;
    printf("%s\n", command);
    token = strtok_r(command, " ", &strptr);
    while (token != NULL)
    {
        if (AreSame(token, "-command"))
        {
            token = strtok_r(NULL, " ", &strptr);
            strcpy(temp, token);
            token = strtok_r(NULL, " ", &strptr);
            while (token != NULL && !AreSame(token, "-interval") && !AreSame(token, "-period"))
            {
                strcat(temp, " ");
                strcat(temp, token);
                token = strtok_r(NULL, " ", &strptr);
            }
            // printf("%s\n",temp);
        }
        if (AreSame(token, "-interval"))
        {
            token = strtok_r(NULL, " ", &strptr);
            strcpy(interval, token);

            // token = strtok_r(NULL, " ", &strptr);// token = "-period"
            // token = strtok_r(NULL, " ", &strptr);
            // strcpy(period, token);
            // break;
        }
       
        if (AreSame(token, "-period"))
        {
            token = strtok_r(NULL, " ", &strptr);
            strcpy(period, token);
            // break;
        }

        token = strtok_r(NULL, " ", &strptr);
    }

    // int interval_t = string_to_int(interval);
    // int period_t = string_to_int(period);

    // // time_t current_t = time(NULL);
    // // int end_time = current_t + period_t;
    // int n = period_t / interval_t;
    // printf("%s %d %d  n = %d\n", temp, interval_t, period_t, n);

    // for (int i = 0; i < n; i++)
    // {
    //     // printf("%s\n", temp);
    //     sleep(interval_t);
    //     process_command(temp);
    // }
    // return;
    // printf("end\n");
    // // process_command(temp);
}
// replay -command echo "hello world" -interval 2 -period 10