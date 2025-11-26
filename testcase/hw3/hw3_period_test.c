// period-test.c
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

int main(int argc, char *argv[])
{
    int ok = 1;
    int period = 15;
    if (setperiod(period) < 0)
    {
        printf("TEST FAILED: set period failed\n");
        exit(1);
    }

    int prev = uptime();
    for (int i = 0; i < 5; i++)
    {
        job(1);
        wait_until_next_period();

        int now = uptime();
        int diff = now - prev;
        if (diff != period)
        {
            printf("TEST FAILED: period mismatch (expected %d, got %d)\n", period, diff);
            ok = 0;
            break;
        }

        prev = now;
    }

    if (ok)
        printf("TEST PASSED!\n");
    else
        printf("TEST FAILED!\n");
}