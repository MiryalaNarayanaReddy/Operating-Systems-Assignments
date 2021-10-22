#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("usage: strace <mask> command [ args ]\n");
        exit(0);
    }
    else
    {
        int msk = atoi(argv[1]);
        trace(msk);
        exec(argv[2], argv + 2);
    }
    exit(0);
}