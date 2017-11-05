#!/bin/bash

make build;

export OMP_NUM_THREADS=1
        printf "THREAD  1 %.20s SECONDS %s\n" "...................." $(./parallel_snake big_input fis 20000)

for((i=1;i<=4;i++))
do
        export OMP_NUM_THREADS=$((i * 2))
        printf "THREAD %2d %.20s SECONDS %s\n" $((i * 2)) "...................." $(./parallel_snake big_input fis 20000)
done

for((i=2;i<=4;i++))
do
        export OMP_NUM_THREADS=$((i * 8))
        printf "THREAD %2d %.20s SECONDS %s\n" $((i * 8)) "...................." $(./parallel_snake big_input fis 20000)
done

make clean
