#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include "test_instr.h"

void test_rdcycle(void)
{
    uint64_t v;
    asm volatile("rdcycle %0" : "=r"(v));
    printf("value=%lu ", v);
}

void test_rdinstret(void)
{
    uint64_t v;
    asm volatile("rdinstret %0" : "=r"(v));
    printf("value=%lu ", v);
}

void test_csrr_cycle(void)
{
    uint64_t v;
    asm volatile("csrr %0, cycle" : "=r"(v));
    printf("value=%lu ", v);
}

void test_rdtime(void)
{
    uint64_t v;
    asm volatile("rdtime %0" : "=r"(v));
    printf("value=%lu ", v);
}

void test_fence(void)
{
    asm volatile("fence" ::: "memory");
}

void test_fencei(void)
{
    asm volatile("fence.i");
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

void test_rdcycle_pseudo(void)
{
    unsigned long val;
    asm volatile("rdcycle %0" : "=r"(val));
}

void test_cycle_csrrs(void)
{
    unsigned long val;
    asm volatile("csrrs %0, cycle, x0" : "=r"(val));
}

void test_rdinstret_pseudo(void)
{
    unsigned long val;
    asm volatile("rdinstret %0" : "=r"(val));
}

void test_instret_csrrs(void)
{
    unsigned long val;
    asm volatile("csrrs %0, instret, x0" : "=r"(val));
}

void test_rdtime_pseudo(void)
{
    unsigned long val;
    asm volatile("rdtime %0" : "=r"(val));
}

void test_time_csrrs(void)
{
    unsigned long val;
    asm volatile("csrrs %0, time, x0" : "=r"(val));
}

void test_dcache_civa_stack(void)
{
    volatile int x = 42;
    void *addr = (void *)&x;

    asm volatile(
        "xor a7, a7, a7\n"
        "add a7, a7, %0\n"
        ".long 0x0278800b\n"
        :
        : "r"(addr)
        : "a7", "memory");
}

void test_dcache_civa_mmap(void)
{
    size_t page = sysconf(_SC_PAGESIZE);

    void *buf = mmap(NULL, page,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS,
                     -1, 0);

    if (buf == MAP_FAILED)
        return;

    *(volatile int *)buf = 123;

    asm volatile(
        "xor a7, a7, a7\n"
        "add a7, a7, %0\n"
        ".long 0x0278800b\n"
        :
        : "r"(buf)
        : "a7", "memory");

    munmap(buf, page);
}
