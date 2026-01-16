#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

static sigjmp_buf jmpbuf;
static const char *current_test;

static void sigill_handler(int sig)
{
  printf("[FAIL] %s : SIGILL (illegal instruction)\n", current_test);
  siglongjmp(jmpbuf, 1);
}

void test_run(const char *name, void (*fn)(void))
{
  current_test = name;

  if (sigsetjmp(jmpbuf, 1) == 0)
  {
    fn();
    printf("[ OK ] %s\n", name);
  }
}
void test_framework_init(void)
{
  struct sigaction sa = {0};
  sa.sa_handler = sigill_handler;
  sigaction(SIGILL, &sa, NULL);
}
