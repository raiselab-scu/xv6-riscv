// calc-test.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int test_cases_total = 17;
    int test_cases_passed = 0;
    int res = 0;
    char op;
    int error_code;

    // base cases
    op = '+'; error_code = calculate(10, 20, &op, &res);
    if (res == 30 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=10, b=20, op='%c' | got (res=%d, error_code=%d), expected (res=30, error_code=0)\n", op, res, error_code);
    }

    op = '-'; error_code = calculate(10, 20, &op, &res);
    if (res == -10 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=10, b=20, op='%c' | got (res=%d, error_code=%d), expected (res=-10, error_code=0)\n", op, res, error_code);
    }

    op = '*'; error_code = calculate(4, 5, &op, &res);
    if (res == 20 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=4, b=5, op='%c' | got (res=%d, error_code=%d), expected (res=20, error_code=0)\n", op, res, error_code);
    }

    op = '/'; error_code = calculate(6, 3, &op, &res);
    if (res == 2 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=6, b=3, op='%c' | got (res=%d, error_code=%d), expected (res=2, error_code=0)\n", op, res, error_code);
    }

    op = '*'; error_code = calculate(0, 1000, &op, &res);
    if (res == 0 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=0, b=1000, op='%c' | got (res=%d, error_code=%d), expected (res=0, error_code=0)\n", op, res, error_code);
    }

    op = '/'; error_code = calculate(-9, -3, &op, &res);
    if (res == 3 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=-9, b=-3, op='%c' | got (res=%d, error_code=%d), expected (res=3, error_code=0)\n", op, res, error_code);
    }

    op = '-'; error_code = calculate(42, 42, &op, &res);
    if (res == 0 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=42, b=42, op='%c' | got (res=%d, error_code=%d), expected (res=0, error_code=0)\n", op, res, error_code);
    }

    op = '/'; error_code = calculate(9, 9, &op, &res);
    if (res == 1 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=9, b=9, op='%c' | got (res=%d, error_code=%d), expected (res=1, error_code=0)\n", op, res, error_code);
    }

    op = '+'; error_code = calculate(-5, 15, &op, &res);
    if (res == 10 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=-5, b=15, op='%c' | got (res=%d, error_code=%d), expected (res=10, error_code=0)\n", op, res, error_code);
    }

    op = '-'; error_code = calculate(-10, -20, &op, &res);
    if (res == 10 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=-10, b=-20, op='%c' | got (res=%d, error_code=%d), expected (res=10, error_code=0)\n", op, res, error_code);
    }

    op = '*'; error_code = calculate(-5, 3, &op, &res);
    if (res == -15 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=-5, b=3, op='%c' | got (res=%d, error_code=%d), expected (res=-15, error_code=0)\n", op, res, error_code);
    }

    op = '/'; error_code = calculate(-10, 2, &op, &res);
    if (res == -5 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=-10, b=2, op='%c' | got (res=%d, error_code=%d), expected (res=-5, error_code=0)\n", op, res, error_code);
    }

    op = '/'; error_code = calculate(0, 5, &op, &res);
    if (res == 0 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=0, b=5, op='%c' | got (res=%d, error_code=%d), expected (res=0, error_code=0)\n", op, res, error_code);
    }

    op = '/'; error_code = calculate(10, 0, &op, &res);
    if (res == 0 && error_code == -1) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=10, b=0, op='%c' | got (res=%d, error_code=%d), expected (res=0, error_code=-1)\n", op, res, error_code);
    }

    op = '&'; error_code = calculate(10, 0, &op, &res);
    if (res == 0 && error_code == -1) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=10, b=0, op='%c' | got (res=%d, error_code=%d), expected (res=0, error_code=-1)\n", op, res, error_code);
    }

    op = '/'; error_code = calculate(7, 2, &op, &res);
    if (res == 3 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=7, b=2, op='%c' | got (res=%d, error_code=%d), expected (res=3, error_code=0)\n", op, res, error_code);
    }

    op = '+'; error_code = calculate(0, 0, &op, &res);
    if (res == 0 && error_code == 0) {
      test_cases_passed++;
    } else {
      printf("Test failed: a=0, b=0, op='%c' | got (res=%d, error_code=%d), expected (res=0, error_code=0)\n", op, res, error_code);
    }

    if(test_cases_passed == test_cases_total) {
        printf("All %d test cases passed!\n", test_cases_total);
    } else {
        printf("%d out of %d test cases passed.\n", test_cases_passed, test_cases_total);
    }

    exit(0);
}