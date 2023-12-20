#!/bin/bash

# Calculate experiment results of number threads on different size matrix
g++ -fopenmp -o par.exe par.cpp

echo "Run experiment"
printf "\n"

echo "Try 10*10 matrix... "
./par.exe 10 results10.txt experiment
printf "\n"

echo "Try 100*100 matrix... "
./par.exe 100 results100.txt experiment
printf "\n"

echo "Try 250*250 matrix... "
./par.exe 250 results250.txt experiment
printf "\n"

echo "Try 500*500 matrix... "
./par.exe 500 results500.txt experiment
printf "\n"

echo "Try 750*750 matrix... "
./par.exe 750 results750.txt experiment
printf "\n"

echo "Try 1000*1000 matrix... "
./par.exe 1000 results1000.txt experiment
printf "\n"