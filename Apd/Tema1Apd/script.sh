#!/bin/bash

make build;

echo "test 1"
export OMP_NUM_THREADS=1
        printf "THREAD  1 %.20s SECONDS %s\n" "...................." $(./parallel_snake teste/input1 fis 20000)
        diff fis teste/output1

for((i=1;i<=4;i++))
do
        export OMP_NUM_THREADS=$((i * 2))
        printf "THREAD %2d %.20s SECONDS %s\n" $((i * 2)) "...................." $(./parallel_snake teste/input1 fis 20000)
        diff fis teste/output1
done

for((i=2;i<=4;i++))
do
        export OMP_NUM_THREADS=$((i * 8))
        printf "THREAD %2d %.20s SECONDS %s\n" $((i * 8)) "...................." $(./parallel_snake teste/input1 fis 20000)
        diff fis teste/output1
done

echo "test 2"
export OMP_NUM_THREADS=1
        printf "THREAD  1 %.20s SECONDS %s\n" "...................." $(./parallel_snake teste/input2 fis 20000)
        diff fis teste/output2

for((i=1;i<=4;i++))
do
        export OMP_NUM_THREADS=$((i * 2))
        printf "THREAD %2d %.20s SECONDS %s\n" $((i * 2)) "...................." $(./parallel_snake teste/input2 fis 20000)
        diff fis teste/output2
done

for((i=2;i<=4;i++))
do
        export OMP_NUM_THREADS=$((i * 8))
       printf "THREAD %2d %.20s SECONDS %s\n" $((i * 8)) "...................." $(./parallel_snake teste/input2 fis 20000)
        diff fis teste/output2
done

# echo "big"
# export OMP_NUM_THREADS=1
#         printf "THREAD  1 %.20s SECONDS %s\n"  "...................." $(./parallel_snake big_input fis 20000)

# for((i=1;i<=4;i++))
# do
#         export OMP_NUM_THREADS=$((i * 2))
#         printf "THREAD %2d %.20s SECONDS %s\n" $((i * 2)) "...................." $(./parallel_snake teste/big_input fis 20000)
#         diff fis teste/big_output
# done

# for((i=2;i<=4;i++))
# do
#         export OMP_NUM_THREADS=$((i * 8))
#         printf "THREAD %2d %.20s SECONDS %s\n" $((i * 8)) "...................." $(./parallel_snake teste/big_input fis 20000)
#         diff fis teste/big_ouput
# done
# make clean
