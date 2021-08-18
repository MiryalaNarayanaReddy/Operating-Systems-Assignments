#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char progress_bar[101];

size_t length_of_string(char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

void print_to_console(char *s)
{
    write(1, s, length_of_string(s));
}

//100.00 % [####################################################################################################]

void showprogress(float progress)
{
    fflush(stdout);
    print_to_console("\r");
    for (int i = 0; i < progress; i++)
    {
        progress_bar[i] = '#';
    }
    char temp[115];

    sprintf(temp, "%5.2f %% [%-100s]", progress, progress_bar);
    print_to_console(temp);
}

int main()
{
    progress_bar[100] = '\0';
    float i = 0;
    for (; i < 100; i += 1)
    {
        showprogress(i);
        sleep(1);
    }
    showprogress(100);
    print_to_console("\n");
}


