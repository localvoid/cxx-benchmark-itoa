#!/bin/bash

BPATH=../build/

benchmarks=(
  naive
  2pass_1b
  2pass_2b_1
  2pass_2b_2
  2pass_2b_3
  copy_2b
)

function mkgraph {
  ./graph.R < $1 $2
}

function cold_bench {
  echo "Generating cold data"
  echo "Name,Digits,Time" > $1
  for x in {1..100}; do
    for i in ${benchmarks[@]}; do
      DIGITS=20
      while [ $DIGITS -gt 0 ]; do
        $BPATH$i 1 $DIGITS >> $1
        let DIGITS-=1
      done
    done
  done
}

function hot_bench {
  echo "Generating hot data"
  echo "Name,Digits,Time" > $1
  for x in {1..100}; do
    for i in ${benchmarks[@]}; do
      $BPATH$i 1000 >> $1
    done
  done
}


hot_bench "hot.csv"
cold_bench "cold.csv"

mkgraph "hot.csv" "hot.pdf"
mkgraph "cold.csv" "cold.pdf"
