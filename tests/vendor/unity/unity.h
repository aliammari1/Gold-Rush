/* SPDX-License-Identifier: MIT */
/*
 * Minimal Unity-compatible test harness.
 *
 * This is a tiny, self-contained subset of the ThrowTheSwitch "Unity"
 * test framework API (https://github.com/ThrowTheSwitch/Unity, MIT). It
 * implements only the macros used by Gold Rush's tests so the suite has
 * zero network/vendoring footprint and compiles with a bare C compiler.
 *
 * To swap in upstream Unity, drop unity.c/unity.h/unity_internals.h here
 * and delete this shim; the test source uses the standard Unity API.
 */
#ifndef UNITY_H
#define UNITY_H

#include <stdio.h>

extern int unity_tests_run;
extern int unity_tests_failed;
extern const char *unity_current_test;

void unity_begin(void);
int unity_end(void);
void unity_run_test(void (*func)(void), const char *name);
void unity_fail(const char *file, int line, const char *msg);

#define UNITY_BEGIN() (unity_begin(), 0)
#define UNITY_END() unity_end()

#define RUN_TEST(func) unity_run_test(func, #func)

#define TEST_FAIL_MESSAGE(msg) \
    unity_fail(__FILE__, __LINE__, (msg))

#define TEST_ASSERT_TRUE(cond)                                  \
    do {                                                        \
        if (!(cond)) {                                          \
            unity_fail(__FILE__, __LINE__,                      \
                       "Expected TRUE: " #cond);                \
            return;                                             \
        }                                                       \
    } while (0)

#define TEST_ASSERT_FALSE(cond)                                 \
    do {                                                        \
        if ((cond)) {                                           \
            unity_fail(__FILE__, __LINE__,                      \
                       "Expected FALSE: " #cond);               \
            return;                                             \
        }                                                       \
    } while (0)

#define TEST_ASSERT_EQUAL_INT(expected, actual)                 \
    do {                                                        \
        long _e = (long)(expected);                             \
        long _a = (long)(actual);                               \
        if (_e != _a) {                                         \
            char _buf[160];                                     \
            snprintf(_buf, sizeof(_buf),                        \
                     "Expected %ld, was %ld (%s)",              \
                     _e, _a, #actual);                          \
            unity_fail(__FILE__, __LINE__, _buf);               \
            return;                                             \
        }                                                       \
    } while (0)

#define TEST_ASSERT_NOT_EQUAL_INT(expected, actual)             \
    do {                                                        \
        long _e = (long)(expected);                             \
        long _a = (long)(actual);                               \
        if (_e == _a) {                                         \
            char _buf[160];                                     \
            snprintf(_buf, sizeof(_buf),                        \
                     "Expected NOT %ld (%s)", _e, #actual);     \
            unity_fail(__FILE__, __LINE__, _buf);               \
            return;                                             \
        }                                                       \
    } while (0)

#endif /* UNITY_H */
