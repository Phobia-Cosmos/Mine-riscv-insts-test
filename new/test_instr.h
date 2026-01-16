#pragma once
#include <stdint.h>

/* 声明所有测试 */
void test_rdcycle(void);
void test_rdinstret(void);
void test_rdtime(void);
void test_csrr_cycle(void);
void test_fence(void);
void test_fencei(void);

void test_nop(void);
void test_mv(void);
void test_add(void);
void test_add_self(void);

void test_fence(void);
void test_fencei(void);

void test_mul(void);
void test_div(void);

void test_fadd_s(void);
void test_fclass_s(void);

void test_c_nop(void);
void test_c_add(void);
void test_c_mv(void);

void test_rdcycle_pseudo(void);
void test_cycle_csrrs(void);

void test_rdinstret_pseudo(void);
void test_instret_csrrs(void);

void test_rdtime_pseudo(void);
void test_time_csrrs(void);

void test_dcache_civa_stack(void);
void test_dcache_civa_mmap(void);

/* 自动注册宏 */
#define TEST_CASE(name) {#name, test_##name}
