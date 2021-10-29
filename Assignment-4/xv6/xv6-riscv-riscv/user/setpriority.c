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
        int new_priority = atoi(argv[1]);
        int pid = atoi(argv[2]);
      //  printf("%d %d\n",new_priority,pid);
        set_priority(new_priority,pid);
        // setting priority
    }
    exit(0);
}