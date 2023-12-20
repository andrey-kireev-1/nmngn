#!/bin/bash

# Try to calculate with sequential mode
g++ -o seq.exe seq.cpp

echo "Sequential mode"
printf "\n"

echo "Try 10*10 matrix: "
./seq.exe 10 test_seq.txt
printf "\n"
echo "Is correct in 10*10 matrix: "
python3 ./test.py test_seq.txt
printf "\n"

echo "Try 100*100 matrix: "
./seq.exe 100 test_seq.txt
printf "\n"
echo "Is correct in 100*100 matrix: "
python3 ./test.py test_seq.txt
printf "\n"

echo "Try 500*500 matrix: "
./seq.exe 500 test_seq.txt
printf "\n"
echo "Is correct in 500*500 matrix: "
python3 ./test.py test_seq.txt
printf "\n"

echo "Try 1000*1000 matrix: "
./seq.exe 1000 test_seq.txt
printf "\n"
echo "Is correct in 1000*1000 matrix: "
python3 ./test.py test_seq.txt
printf "\n"

rm -f test_seq.txt

# Try to calculate with parallel mode
g++ -fopenmp -o par.exe par.cpp

echo "Parallel mode (3 Threads)"
printf "\n"

echo "Try 10*10 matrix: "
./par.exe 10 test_par.txt no_experiment
printf "\n"
echo "Is correct in 10*10 matrix: "
python3 ./test.py test_par.txt
printf "\n"

echo "Try 100*100 matrix: "
./par.exe 100 test_par.txt no_experiment
printf "\n"
echo "Is correct in 100*100 matrix: "
python3 ./test.py test_par.txt
printf "\n"

echo "Try 500*500 matrix: "
./par.exe 500 test_par.txt no_experiment
printf "\n"
echo "Is correct in 500*500 matrix: "
python3 ./test.py test_par.txt
printf "\n"

echo "Try 1000*1000 matrix: "
./par.exe 1000 test_par.txt no_experiment
printf "\n"
echo "Is correct in 1000*1000 matrix: "
python3 ./test.py test_par.txt
printf "\n"

rm -f test_par.txt



