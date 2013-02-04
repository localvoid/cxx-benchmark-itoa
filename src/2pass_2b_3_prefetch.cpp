#include <cstdint>
#include <string.h>
#include "benchmark.hpp"

const char *benchmark::name = "2pass_2b_3_prefetch";


const char digit_pairs[201] = {
  "00010203040506070809"
  "10111213141516171819"
  "20212223242526272829"
  "30313233343536373839"
  "40414243444546474849"
  "50515253545556575859"
  "60616263646566676869"
  "70717273747576777879"
  "80818283848586878889"
  "90919293949596979899"
};


uint32_t benchmark::itoa(uint64_t v, char * const dst) {
  __builtin_prefetch(&digit_pairs[0]);
  auto const size = digits10(v);
  char * c = &dst[size-1];

  while (v >= 100) {
    auto const r = v % 100;
    v /= 100;
    memcpy(c-1, digit_pairs+2*r, 2);
    c -= 2;
  }
  if (v < 10) {
    *c = '0' + v;
  } else {
    memcpy(c-1, digit_pairs+2*v, 2);
  }
  return size;
}
