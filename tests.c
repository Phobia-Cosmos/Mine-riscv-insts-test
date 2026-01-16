#include <stdio.h>
#include "instr.h"

void test_rdcycle(void)
{
  size_t c = rdcycle();
  printf("  rdcycle = %zu\n", c);
}

void test_rdinstret(void)
{
  size_t i = rdinstret();
  printf("  rdinstret = %zu\n", i);
}

void test_rdtime(void)
{
  uint64_t t = rdtime();
  printf("  rdtime = %lu\n", t);
}

void test_csrr_cycle(void)
{
  printf("  csrr cycle = %lu\n", get_cycle_perf());
}

void test_fence(void)
{
  fence_all();
}

void test_fencei(void)
{
  fencei();
}

// -----基础整数指令（最安全）
void test_nop(void)
{
  asm volatile("nop");
}

void test_mv(void)
{
  asm volatile("mv a0, a1" ::: "a0");
}

void test_add(void)
{
  asm volatile("add a0, a1, a2" ::: "a0");
}

void test_add_self(void)
{
  asm volatile("add a1, a1, a1" ::: "a1");
}

// -----M 扩展（如果内核/CPU不支持会 SIGILL）
void test_mul(void)
{
  asm volatile("mul a0, a1, a2" ::: "a0");
}

void test_div(void)
{
  asm volatile("div a0, a1, a2" ::: "a0");
}

// -----F 扩展（Milk‑V 上极可能 SIGILL）
void test_fadd_s(void)
{
  asm volatile("fadd.s f0, f1, f2" ::: "f0");
}

void test_fclass_s(void)
{
  asm volatile("fclass.s a0, f0" ::: "a0");
}

// -----C 扩展（Compressed）
void test_c_nop(void)
{
  asm volatile("c.nop");
}

void test_c_add(void)
{
  asm volatile("c.add a0, a1" ::: "a0");
}

void test_c_mv(void)
{
  asm volatile("c.mv a0, a1" ::: "a0");
}
