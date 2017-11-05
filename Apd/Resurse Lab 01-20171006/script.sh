#!/bin/bash

gcc -fopenmp omp_reduction.c -o omp_reduction

./omp_reduction