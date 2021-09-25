#include "history.h"

void history(char *num)
{
    // print whole history
    if (AreSame(num, ""))
    {
        FILE *fp = fopen(history_file_path, "r");
        if (fp == NULL)
        {
            Color_On(__RED, !BOLD);
            printf("Failed to access history.txt file\n");
            Color_Off();
        }
        char temp[100];
        fscanf(fp, "%s", temp);
        while (!feof(fp))
        {
            printf("%s\n", temp);
            fscanf(fp, "%s", temp);
        }
        printf("%s\n", temp);
        fclose(fp);
        return;
    }

    // convert num to integer
    int n = string_to_int(num);
    if (n == -1)
    {
        printf("%s is not a number\n", num);
        return;
    }

    // print only n lines of history
    FILE *fp = fopen(history_file_path, "r");
    char temp[100];
    int i = 0;
    fscanf(fp, "%s", temp);
    while (i < n && !feof(fp))
    {
        printf("%s\n", temp);
        i++;
        fscanf(fp, "%s", temp);
    }
    fclose(fp);
    return;
}

void push_into_history(char *command)
{
    if (number_of_lines_in_history != 20)
    {

        FILE *fp = fopen(history_file_path, "a");
        fprintf(fp, "\n%s", command);
        fclose(fp);
        return;
    }
    else
    {
        //////// pending
    }
}


