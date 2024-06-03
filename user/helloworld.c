#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    write(1, "Hello World xv6", 15);
    write(1, "\n", 1);
    exit(0);
}
