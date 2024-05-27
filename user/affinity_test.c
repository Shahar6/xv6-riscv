#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;
  i=0b11;
  set_affinity_mask(i);
  int pid = getpid();
  for(;;){
    printf("pid: %d\n", pid);
    pid = getpid();
  }
  exit(0);
}
