// ipc_shared_memory.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "../../user/user.h"

typedef struct
{
    int client_id;
    int x;
    int y;
    char op;
} task_t;

typedef struct
{
    int x;
    int y;
    char op;
    int expected_result;
    int expected_error;
} TestCase;

typedef struct
{
    int client_id;
    int result;
    int error;
    volatile int is_valid;
} client_slot;

TestCase tests[] = {
    {7, 3, '+', 10, 0},
    {20, 5, '-', 15, 0},
    {9, 9, '/', 1, 0},
    {15, 4, '*', 60, 0},
    {12, 0, '/', 0, -1}, 
    {100, 7, '%', 0, -1},
    {-8, 2, '/', -4, 0},
    {-10, 3, '*', -30, 0},
    {50, -6, '+', 44, 0},
    {-9, -9, '-', 0, 0}};

int calcu(int x, int y, char op, int *result)
{
    switch (op)
    {
    case '+':
        *result = x + y;
        return 0;
    case '-':
        *result = x - y;
        return 0;
    case '*':
        *result = x * y;
        return 0;
    case '/':
        if (y == 0)
        {
            *result = 0;
            return -1;
        }
        *result = x / y;
        return 0;
    default:
        *result = 0;
        return -1;
    }
}

void server(int read_fd, client_slot *shm, int num_clients)
{
    task_t task;
    for (int i = 0; i < num_clients; i++)
    {
        int r = read(read_fd, &task, sizeof(task_t));
        if (r <= 0)
        {
            exit(1);
        }

        int res = 0;
        int err = calcu(task.x, task.y, task.op, &res);

        int id = task.client_id;
        shm[id].client_id = id;
        shm[id].result = res;
        shm[id].error = err;
        shm[id].is_valid = (err == 0 ? 1 : -1);
    }
    exit(0);
}

void client(int write_fd, client_slot *shm, int client_id, TestCase tc, int *result_check)
{
    task_t t;
    t.client_id = client_id;
    t.x = tc.x;
    t.y = tc.y;
    t.op = tc.op;

    if (write(write_fd, &t, sizeof(task_t)) != sizeof(task_t))
    {
        printf("TEST FAILED!: write fail\n");
        exit(1);
    }

    while (shm[client_id].is_valid == 0)
    {
        sleep(5);
    }

    int r = shm[client_id].result;
    int e = shm[client_id].error;

    if (r == tc.expected_result && e == tc.expected_error)
        result_check[client_id] = 1;
    else
        result_check[client_id] = 0;

    exit(0);
}

int main()
{
    int n = 10;

    int pipefd[2];
    if (pipe(pipefd) < 0)
    {
        printf("TEST FAILED!: pipe fail\n");
        exit(1);
    }

    uint64 va = shmget(0, 4096);
    if (va == (uint64)-1)
    {
        printf("TEST FAILED!: shmget() syscall fail\n");
        exit(1);
    }

    client_slot *slots = (client_slot *)va;

    for (int i = 0; i < n; i++)
    {
        slots[i].client_id = -1;
        slots[i].result = 0;
        slots[i].error = 0;
        slots[i].is_valid = 0;
    }

    int *result_check = (int *)(va + sizeof(client_slot) * n);

    for (int i = 0; i < n; i++)
        result_check[i] = 0;

    if (fork() == 0)
    {
        close(pipefd[1]);
        server(pipefd[0], slots, n);
    }

    close(pipefd[0]);

    for (int i = 0; i < n; i++)
    {
        if (fork() == 0)
        {
            client(pipefd[1], slots, i, tests[i], result_check);
        }
    }

    close(pipefd[1]);

    for (int i = 0; i < n + 1; i++)
        wait(0);

    int pass = 1;
    for (int i = 0; i < n; i++)
    {
        if (result_check[i] != 1)
        {
            printf("TEST FAILED!: test case %d failed\n", i);
            pass = 0;
            break;
        }
    }

    if (pass)
        printf("TEST PASSED!\n");
    else
        printf("TEST FAILED!\n");

    exit(0);
}
