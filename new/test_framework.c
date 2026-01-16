#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>

#include "test_framework.h"
#include "test_instr.h"

// static jmp_buf ill_jmp;
static sigjmp_buf ill_jmp;

// static void sigill_handler(int signo)
// {
//     (void)signo;
//     longjmp(ill_jmp, 1);
// }
static void sigill_handler(int signo)
{
    (void)signo;
    siglongjmp(ill_jmp, 1);
}

// void test_framework_init(void)
// {
//     struct sigaction sa;
//     memset(&sa, 0, sizeof(sa));
//     sa.sa_handler = sigill_handler;
//     sigaction(SIGILL, &sa, NULL);
// }
void test_framework_init(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = sigill_handler;
    sigemptyset(&sa.sa_mask); // ⚠️ 非常关键
    sa.sa_flags = 0;

    sigaction(SIGILL, &sa, NULL);
}

/* ---------- 自动测试表 ---------- */

typedef struct
{
    const char *name;
    test_fn_t fn;
} test_case_t;

static test_case_t tests[] = {
    /* ---- CSR / Timer ---- */
    TEST_CASE(rdcycle),
    TEST_CASE(rdinstret),
    TEST_CASE(rdtime),
    TEST_CASE(csrr_cycle),

    /* ---- Barriers ---- */
    TEST_CASE(fence),
    TEST_CASE(fencei),

    /* ---- Integer (base) ---- */
    TEST_CASE(nop),
    TEST_CASE(mv),
    TEST_CASE(add),
    TEST_CASE(add_self),

    /* ---- M extension ---- */
    TEST_CASE(mul),
    TEST_CASE(div),

    /* ---- F extension ---- */
    TEST_CASE(fadd_s),
    TEST_CASE(fclass_s),

    /* ---- C extension ---- */
    TEST_CASE(c_nop),
    TEST_CASE(c_add),
    TEST_CASE(c_mv),

    /* ---- cycle ---- */
    TEST_CASE(rdcycle_pseudo),
    TEST_CASE(cycle_csrrs),

    /* ---- instret ---- */
    TEST_CASE(rdinstret_pseudo),
    TEST_CASE(instret_csrrs),

    /* ---- time ---- */
    TEST_CASE(rdtime_pseudo),
    TEST_CASE(time_csrrs),

    TEST_CASE(dcache_civa_stack),
    TEST_CASE(dcache_civa_mmap),

    {NULL, NULL}};

void test_run_all(void)
{
    for (int i = 0; tests[i].name; i++)
    {
        printf("[TEST] %-16s : ", tests[i].name);

        if (sigsetjmp(ill_jmp, 1) == 0)
        {
            tests[i].fn();
            printf("OK\n");
        }
        else
        {
            printf("SIGILL\n");
        }
    }
}
