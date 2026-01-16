#pragma once
#include <stdint.h>
#include <stddef.h>

static inline size_t rdinstret()
{
  size_t val;
  asm volatile("rdinstret %0" : "=r"(val));
  return val;
}

static inline size_t rdcycle()
{
  size_t val;
  asm volatile("rdcycle %0" : "=r"(val));
  return val;
}

static inline uint64_t rdtime()
{
  uint64_t val;
  asm volatile("rdtime %0" : "=r"(val));
  return val;
}

static inline uint64_t get_cycle_perf()
{
  uint64_t val;
  asm volatile("csrr %0, cycle" : "=r"(val));
  return val;
}

static inline uint64_t get_time_perf()
{
  uint64_t val;
  asm volatile("csrr %0, time" : "=r"(val));
  return val;
}

static inline uint64_t get_retire_perf()
{
  uint64_t val;
  asm volatile("csrr %0, instret" : "=r"(val));
  return val;
}

static inline void fencei()
{
  asm volatile("fence.i");
}

static inline void fence_all()
{
  asm volatile("fence");
}

