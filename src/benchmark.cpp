#include <cstdint>
#include <iostream>
#include <string.h>
#ifdef ENABLE_CPU_AFFINITY
#  include <sched.h>
#endif

#include "benchmark.hpp"

namespace {

const uint64_t Numbers[20] = {
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
  10000000000000000000U
};


#if defined(__i386__)
uint64_t rdtsc() {
  uint64_t x;
  __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
  return x;
}
#elif defined(__x86_64__)
uint64_t rdtsc() {
  uint32_t hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)lo)|(((uint64_t)hi)<<32 );
}
#endif

template<typename T>
uint64_t measure(T code) {
  uint64_t a = rdtsc();

  code();

  uint64_t b = rdtsc();

  return (b - a);
}

void run(int loop_count) {
  int digits = 1;
  char buf[32];

  for (auto i: Numbers) {
    uint64_t time = measure([i, loop_count, &buf]() {
        for (int x = 0; x < loop_count; ++x) {
          benchmark::itoa(i, buf);
        }
      });

    std::cout << benchmark::name << ',' << digits << ',' << time/loop_count << std::endl;
    digits++;
  }
}

void run(int loop_count, int digits) {
  char buf[32];

  auto i = Numbers[digits-1];
  uint64_t time = measure([i, loop_count, &buf]() {
      for (int x = 0; x < loop_count; ++x) {
        benchmark::itoa(i, buf);
      }
    });

  std::cout << benchmark::name << ',' << digits << ',' << time/loop_count << std::endl;
}

}

int main(int argc, char *argv[]) {
#ifdef ENABLE_CPU_AFFINITY
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(0, &mask);
  if (sched_setaffinity(0, sizeof(mask), &mask) < 0) {
    perror("sched_setaffinity");
  }
#endif

  int loop_count = 1;
  int digits = -1;

  if (argc > 1) {
    loop_count = atoi(argv[1]);
    if (loop_count < 1) {
      std::cerr << "Invalid argument: loop counter" << std::endl;
      return 1;
    }

    if (argc > 2) {
      digits = atoi(argv[2]);

      if (digits < 1 || digits > 20) {
        std::cerr << "Invalid argument: digit count is out of range" << std::endl;
        return 1;
      }
    }
  }

  if (digits == -1) {
    run(loop_count);
  } else {
    run(loop_count, digits);
  }


  return 0;
}
