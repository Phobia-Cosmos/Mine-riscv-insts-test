#include <stdio.h>

void test_framework_init(void);
void test_run(const char *name, void (*fn)(void));

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

int main()
{
  test_framework_init();

  test_run("rdcycle", test_rdcycle);
  test_run("rdinstret", test_rdinstret);
  test_run("rdtime", test_rdtime);
  test_run("csrr cycle", test_csrr_cycle);
  test_run("fence", test_fence);
  test_run("fence.i", test_fencei);

  return 0;
}
