#ifndef _BENCHMARK_HPP_
#define _BENCHMARK_HPP_

namespace benchmark {

uint32_t itoa(uint64_t v, char *dst);

extern const char *Name;


#if defined(__i386__)
inline uint64_t rdtsc() {
  uint64_t x;
  asm(".byte 0x0f, 0x31" : "=A" (x));
  return x;
}
#elif defined(__x86_64__)
inline uint64_t rdtsc() {
  uint32_t hi, lo;
  asm("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)lo)|(((uint64_t)hi)<<32 );
}
#endif

template<typename T>
uint64_t measure_cycles(T code) {
  uint64_t a = rdtsc();

  code();

  uint64_t b = rdtsc();

  return (b - a);
}


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

inline unsigned long bsrq(unsigned long mask) {
  unsigned long result;
  asm volatile("bsrq %1,%0" : "=r" (result) : "rm" (mask));
  return result;
}

inline uint32_t digits10(uint64_t n) {
  uint32_t t = (bsrq(n | 1) + 1) * 1233 >> 12;
  return t - (n < powers_of_10[t]) + 1;
}


}

#endif
