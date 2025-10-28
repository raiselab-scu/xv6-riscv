// Prioritized-IPC-test.c
#define TASK_QUEUE_MAX_SIZE 16
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

typedef struct Testcase {
    int priority;
    int x;
    int y;
    char op; // '+', '-', '*', '/'
    int result;
    int error;
} Testcase;

// 17 test cases
Testcase testcases[] = {
    {2, 10, 20, '+', 30, 0},
    {3, 10, 20, '-', -10, 0},
    {4, 4, 5, '*', 20, 0},
    {5, 6, 3, '/', 2, 0},
    {6, 0, 1000, '*', 0, 0},
    {7, -9, -3, '/', 3, 0},
    {8, 42, 42, '-', 0, 0},
    {9, -5, 15, '+', 10, 0},
    {10, -10, -20, '-', 10, 0},
    {11, -5, 3, '*', -15, 0},
    {12, -10, 2, '/', -5, 0},
    {13, 0, 5, '/', 0, 0},
    {14, 7, 2, '/', 3, 0},
    {15, 0, 0, '+', 0, 0},
    {16, 0, 0, '-', 0, 0},
    {17, 10, 0, '/', 0, -1},
    {18, 10, 0, '&', 0, -1},
};