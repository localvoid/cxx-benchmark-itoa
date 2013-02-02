#include <cstdint>
#include <random>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "benchmark.hpp"

namespace {

uint32_t valid_itoa(uint64_t v, char *b) {
  return sprintf(b, "%lu", v);
}


const uint64_t Numbers[] = {
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
  UINT64_MAX
};


void check(uint64_t v) {
  char buf1[32];
  char buf2[32];
  uint32_t s1 = valid_itoa(v, buf1);
  uint32_t s2 = benchmark::itoa(v, buf2);

  if (s1 != s2) {
    std::cout
    << "different sizes on: " << v << std::endl
    << "  sprintf: " << std::string(buf1, s1) << ':' << s1 << std::endl
    << "  custom:  " << std::string(buf2, s2) << ':' << s2 << std::endl;
    return;
  }
  if (memcmp(buf1, buf2, s1) != 0) {
    std::cout
    << "different values on: " << v << std::endl
    << "  sprintf: " << std::string(buf1, s1) << ':' << s1 << std::endl
    << "  custom:  " << std::string(buf2, s2) << ':' << s2 << std::endl;
    return;
  }
}

void simple_test() {
  std::cout << "simple test" << std::endl;

  for (auto i: Numbers)
    check(i);
}


void random_test(uint64_t seed) {
  std::cout << "random test (seed: " << seed << ")" << std::endl;

  std::mt19937 rng;
  std::uniform_int_distribution<uint64_t> uint64_dist;

  rng.seed(seed);
  for (;;) {
    uint64_t v = uint64_dist(rng);
    check(v);
  }
}

}

int main(int argc, char *argv[]) {
  if (argc == 1)
    simple_test();
  else
    random_test(atol(argv[1]));

  return 0;
}
