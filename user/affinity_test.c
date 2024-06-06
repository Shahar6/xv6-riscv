#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;
  i=0b101;
  set_affinity_mask(i);
  int pid = getpid();
  printf("affinity_test PID: %d\n", pid);
  for(;;){
    pid = getpid();
    //printf("pid: %d\n", pid);
  }
  exit(0,0);
}
