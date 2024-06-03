#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int i;

    i = memsize();
    printf("process size: %d", i);
    write(1, "\n", 1);

    char* string = (char*) malloc(20000);

    i = memsize();
    printf("process size after malloc: %d", i);
    write(1, "\n", 1);

    free(string);
    
    i = memsize();
    printf("process size after free: %d", i);
    write(1, "\n", 1);

    exit(0);
}
