#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    int t;
    scanf("%d", &t);
    char a[1200];
    int i = 0;
    for (int i = 0; i < t; i++)
    {
        scanf("%c", &a[i]);
    }
    for (int j = t-1; j >= 0; j--)
    {
        printf("%c", a[j]);
    }
}
