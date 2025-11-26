// affinity-test.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "../../user/user.h"

int main(int argc, char *argv[])
{
  int pid = fork();
  if (pid == 0)
  {
    // bind to CPU 2
    if (set_cpu_affinity(1 << 2) < 0)
    {
      printf("TEST FAILED: set_cpu_affinity( 1 << 2) failed\n");
      exit(1);
    }

    // clear affinity
    if (set_cpu_affinity(0) < 0)
    {
      printf("TEST FAILED: clear affinity failed\n");
      exit(1);
    }

    printf("TEST PASSED\n");
    exit(0);
  }

  wait(0);
  exit(0);
}
