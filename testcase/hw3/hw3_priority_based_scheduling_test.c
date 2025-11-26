// priority-based-scheduling-test.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "../../user/user.h"

void job(int n)
{
    int k;
    const int loop = 1000000;
    for (int i = 0; i < 100; ++i)
    {
        asm("nop");
        if (i % 10 == 0)
        {
            printf("%d ", n);
        }
        for (k = 0; k < loop; ++k)
        {
            asm("nop");
        }
    }
    printf("\n");
}

void periodic_task(int period, int n)
{
    setperiod(period);
    set_cpu_affinity(1 << 0);
    while (1)
    {
        job(n);
        wait_until_next_period();
    }
    exit(0);
}

int main()
{
    int periods[] = {20, 40, 80, 160};
    int num_of_proc = 4;
    for (int i = 0; i < num_of_proc; ++i)
    {
        if (fork() == 0)
        {
            periodic_task(periods[i], i + 1);
        }
    }

    if (fork() == 0)
    {
        sleep(10);
        int ret = setperiod(10);
        if (ret != -1)
        {
            printf("TEST FAILED: set period should fail\n");
            exit(1);
        }
        else
        {
            printf("TEST PASSED: set period failed as expected\n");
        }
        exit(0);
    }

    for (int i = 0; i < 5; ++i)
    {
        wait(0);
    }

    exit(0);
}