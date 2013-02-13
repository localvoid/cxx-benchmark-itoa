#include <cstdint>
#include "benchmark.hpp"

const char *benchmark::Name = "2pass_1b";


uint32_t benchmark::itoa(uint64_t v, char *const dst) {
  auto const size = digits10(v);
  uint32_t pos = size - 1;
  while (v >= 10) {
    auto const r = v % 10;
    v /= 10;
    dst[pos--] = '0' + r;
  }
  *dst = v + '0';
  return size;
}
