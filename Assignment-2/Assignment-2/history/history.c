#include "history.h"

void get_line(FILE *fp, char *buf)
{
    char ch;
    int i = 0;
    fscanf(fp, "%c", &ch);
    while (ch != '\n' && !feof(fp))
    {
        buf[i++] = ch;
        fscanf(fp, "%c", &ch);
    }
    buf[i] = '\0';
}

void history(char *num)
{
    int n = number_of_lines_in_history;
    if (AreSame(num, ""))
    {
        for (int j = ((n - 9) >= 0 ? n - 9 : 0); j <= n; j++)
        {
            printf("%s\n", History[j]);
        }
        return;
    }
    else
    {
        // convert num to integer
        int m = string_to_int(num);
        if (m == -1)
        {
            printf("%s is not a number\n", num);
            return;
        }
        else
        {
            for (int j = (((n - m) + 1) >= 0 ? (n - m) + 1 : 0); j <= n; j++)
            {
                printf("%s\n", History[j]);
            }
            return;
        }
    }
}

void push_into_history(char *command)
{
    if (number_of_lines_in_history != 20)
    {
        number_of_lines_in_history++;
        strcpy(History[number_of_lines_in_history], command);
    }
    else
    {
        int i = 0;
        while (i != 20)
        {
            strcpy(History[i], History[i + 1]);
            i++;
        }
        strcpy(History[i], command);
    }

    FILE *fp = fopen(history_file_path, "w");
    fprintf(fp, "%d", number_of_lines_in_history);
    int n = number_of_lines_in_history;
    for (int j = (n - 19 >= 0 ? n - 19 : 0); j <= n; j++)
    {
        fprintf(fp, "\n%s", History[j]);
    }
    fclose(fp);
}
