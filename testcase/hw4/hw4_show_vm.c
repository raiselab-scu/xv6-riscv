// show_vm_areas.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "../../user/user.h"

int main(int argc, char *argv[])
{
    if (show_vm_areas() == -1)
    {
        printf("TEST FAILED!\n");
    }
    printf("TEST PASSED!\n");
    exit(0);
}