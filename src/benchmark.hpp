#ifndef _BENCHMARK_HPP_
#define _BENCHMARK_HPP_

namespace benchmark {

uint32_t itoa(uint64_t v, char *dst);

extern const char *name;

static const uint64_t powers_of_10[] = {
  0,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
  10000000,
  100000000,
  1000000000,
  10000000000,
  100000000000,
  1000000000000,
  10000000000000,
  100000000000000,
  1000000000000000,
  10000000000000000,
  100000000000000000,
  1000000000000000000,
  10000000000000000000U,
};

static inline unsigned long bsrq(unsigned long mask) {
  unsigned long result;
  asm volatile("bsrq %1,%0" : "=r" (result) : "rm" (mask));
  return result;
}

uint32_t inline digits10(uint64_t n) {
  uint32_t t = (bsrq(n | 1) + 1) * 1233 >> 12;
  return t - (n < powers_of_10[t]) + 1;
}


}

#endif
