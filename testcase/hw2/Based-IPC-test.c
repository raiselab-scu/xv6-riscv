// Prioritized-IPC-test.c
#define TASK_QUEUE_MAX_SIZE 16
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

typedef struct Testcase {
    int x;
    int y;
    char op; // '+', '-', '*', '/'
    int result;
    int error;
} Testcase;

// 17 test cases
Testcase testcases[] = {
    {10, 20, '+', 30, 0},
    {10, 20, '-', -10, 0},
    {4, 5, '*', 20, 0},
    {6, 3, '/', 2, 0},
    {0, 1000, '*', 0, 0},
    {-9, -3, '/', 3, 0},
    {42, 42, '-', 0, 0},
    {-5, 15, '+', 10, 0},
    {-10, -20, '-', 10, 0},
    {-5, 3, '*', -15, 0},
    {-10, 2, '/', -5, 0},
    {0, 5, '/', 0, 0},
    {7, 2, '/', 3, 0},
    {0, 0, '+', 0, 0},
    {0, 0, '-', 0, 0},
    {10, 0, '/', 0, -1},
    {10, 0, '&', 0, -1},
};

int main(){
    return 0;
}