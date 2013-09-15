cmake_minimum_required(VERSION 2.8)

project(benchmark-itoa)


option(ENABLE_CPU_AFFINITY "Set CPU affinity in benchmark applications" OFF)
option(BUILD_TESTS "Build test applications" ON)


set(CXX_WARNING_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-rtti -pipe -std=gnu++11 ${CXX_WARNING_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG    "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE  "-mtune=native -march=native -O2 -g -DNDEBUG")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--hash-style=gnu")

if(ENABLE_CPU_AFFINITY)
  add_definitions( -DENABLE_CPU_AFFINITY )
endif()

function(add_benchmark_executable NAME)
  add_executable(${NAME} src/benchmark.cpp src/${NAME}.cpp)
  if(BUILD_TESTS)
    add_executable(test-${NAME} src/test.cpp src/${NAME}.cpp)
  endif()
endfunction()


add_benchmark_executable(naive)
add_benchmark_executable(2pass_1b)
add_benchmark_executable(2pass_2b_1)
add_benchmark_executable(2pass_2b_2)
add_benchmark_executable(2pass_2b_3)
add_benchmark_executable(copy_2b)
add_benchmark_executable(2pass_2b_3_prefetch)
