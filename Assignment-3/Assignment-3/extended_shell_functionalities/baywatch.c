#include "baywatch.h"
#include <time.h>
#include <termios.h>
#include <sys/ioctl.h>

char scan_char()
{
    struct termios state;

    tcgetattr(0, &state);
    state.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(0, TCSANOW, &state);
    int buffer_count;
    ioctl(0, FIONREAD, &buffer_count);

    tcgetattr(0, &state);
    state.c_lflag |= ICANON | ECHO;

    tcsetattr(0, TCSANOW, &state);

    if (buffer_count == 0)
    {
        return '\0';
    }
    else
    {
        getchar();
    }
}

// baywatch -n 1 interrupt
void baywatch(char *args)
{
    int i = 3; // "-n <number> <str>"
    char interval[10];
    int j = 0;
    while (args[i] != ' ')
    {
        interval[j++] = args[i];
        i++;
    }

    interval[j] = '\0';
    int interval_t = string_to_int(interval);

    printf("%d\n", interval_t);
    char temp[2048];
    if (AreSame(&args[i + 1], "interrupt"))
    {
        char ch;
        FILE *fp;
        fp = fopen("/proc/interrupts", "r");
        if (fp == NULL)
        {
            perror("Failed to read /proc/interrupts");
            return;
        }
        fgets(temp, 2048, fp);
        fclose(fp);
        temp[95] = '\0';
        printf("%s\n", temp + 5);
        while (scan_char() != 'q')
        {
            fp = fopen("/proc/interrupts", "r");
            if (fp == NULL)
            {
                perror("Failed to read /proc/interrupts");
                return;
            }
            fgets(temp, 2048, fp);
            fgets(temp, 2048, fp);
            fgets(temp, 2048, fp);
            fclose(fp);
            temp[95] = '\0';
            printf("%s\n", temp + 5);
            // fflush(stdout);
            sleep(interval_t);
        }
        printf("\n");
    }
    else if (AreSame(&args[i + 1], "newborn"))
    {
    }
    else if (AreSame(&args[i + 1], "dirty"))
    {
    }
}