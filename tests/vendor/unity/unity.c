/* SPDX-License-Identifier: MIT */
#include "unity.h"

int unity_tests_run = 0;
int unity_tests_failed = 0;
const char *unity_current_test = "";

static int unity_current_failed = 0;

void unity_begin(void)
{
    unity_tests_run = 0;
    unity_tests_failed = 0;
}

void unity_run_test(void (*func)(void), const char *name)
{
    unity_current_test = name;
    unity_current_failed = 0;
    unity_tests_run++;
    func();
    if (unity_current_failed) {
        unity_tests_failed++;
        printf("FAIL: %s\n", name);
    } else {
        printf("PASS: %s\n", name);
    }
}

void unity_fail(const char *file, int line, const char *msg)
{
    unity_current_failed = 1;
    printf("  %s:%d: %s\n", file, line, msg);
}

int unity_end(void)
{
    printf("-----------------------\n");
    printf("%d Tests %d Failures\n", unity_tests_run, unity_tests_failed);
    printf("%s\n", unity_tests_failed == 0 ? "OK" : "FAILURES");
    return unity_tests_failed;
}
