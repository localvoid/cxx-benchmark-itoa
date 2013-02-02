#include <cstdint>
#include <algorithm>
#include "benchmark.hpp"

const char *benchmark::name = "naive";

uint32_t benchmark::itoa(uint64_t v, char *dst) {
  char *start = dst;
  do {
    *dst++ = '0' + (v % 10);
    v /= 10;
  } while (v != 0);
  const uint32_t result = dst - start;

  for (dst--; dst > start; start++, dst--) {
    std::iter_swap(dst, start);
  }
  return result;
}
