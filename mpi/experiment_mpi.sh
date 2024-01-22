#!/bin/bash

# Try to experiment of parallel mode MPI with different numbers of threads
mpic++ par_mpi.cpp -o par.exe

echo "Experiment Run"
printf "\n"

echo "Try 10*10 matrix: "
echo "num_threads = 1"
mpirun -np 1 ./par.exe 10 test_par.txt
echo "num_threads = 2"
mpirun -np 2 ./par.exe 10 test_par.txt
echo "num_threads = 3"
mpirun -np 3 ./par.exe 10 test_par.txt
echo "num_threads = 4"
mpirun -np 4 ./par.exe 10 test_par.txt
echo "num_threads = 5"
mpirun -np 5 ./par.exe 10 test_par.txt
echo "num_threads = 6"
mpirun -np 6 ./par.exe 10 test_par.txt
echo "num_threads = 7"
mpirun -np 7 ./par.exe 10 test_par.txt
echo "num_threads = 8"
mpirun -np 8 ./par.exe 10 test_par.txt
echo "num_threads = 9"
mpirun -np 9 ./par.exe 10 test_par.txt
echo "num_threads = 10"
mpirun -np 10 ./par.exe 10 test_par.txt
printf "\n"

echo "Try 100*100 matrix: "
echo "num_threads = 1"
mpirun -np 1 ./par.exe 100 test_par.txt
echo "num_threads = 2"
mpirun -np 2 ./par.exe 100 test_par.txt
echo "num_threads = 3"
mpirun -np 3 ./par.exe 100 test_par.txt
echo "num_threads = 4"
mpirun -np 4 ./par.exe 100 test_par.txt
echo "num_threads = 5"
mpirun -np 5 ./par.exe 100 test_par.txt
echo "num_threads = 6"
mpirun -np 6 ./par.exe 100 test_par.txt
echo "num_threads = 7"
mpirun -np 7 ./par.exe 100 test_par.txt
echo "num_threads = 8"
mpirun -np 8 ./par.exe 100 test_par.txt
echo "num_threads = 9"
mpirun -np 9 ./par.exe 100 test_par.txt
echo "num_threads = 10"
mpirun -np 10 ./par.exe 100 test_par.txt
printf "\n"

echo "Try 250*250 matrix: "
echo "num_threads = 1"
mpirun -np 1 ./par.exe 250 test_par.txt
echo "num_threads = 2"
mpirun -np 2 ./par.exe 250 test_par.txt
echo "num_threads = 3"
mpirun -np 3 ./par.exe 250 test_par.txt
echo "num_threads = 4"
mpirun -np 4 ./par.exe 250 test_par.txt
echo "num_threads = 5"
mpirun -np 5 ./par.exe 250 test_par.txt
echo "num_threads = 6"
mpirun -np 6 ./par.exe 250 test_par.txt
echo "num_threads = 7"
mpirun -np 7 ./par.exe 250 test_par.txt
echo "num_threads = 8"
mpirun -np 8 ./par.exe 250 test_par.txt
echo "num_threads = 9"
mpirun -np 9 ./par.exe 250 test_par.txt
echo "num_threads = 10"
mpirun -np 10 ./par.exe 250 test_par.txt
printf "\n"

echo "Try 500*500 matrix: "
echo "num_threads = 1"
mpirun -np 1 ./par.exe 500 test_par.txt
echo "num_threads = 2"
mpirun -np 2 ./par.exe 500 test_par.txt
echo "num_threads = 3"
mpirun -np 3 ./par.exe 500 test_par.txt
echo "num_threads = 4"
mpirun -np 4 ./par.exe 500 test_par.txt
echo "num_threads = 5"
mpirun -np 5 ./par.exe 500 test_par.txt
echo "num_threads = 6"
mpirun -np 6 ./par.exe 500 test_par.txt
echo "num_threads = 7"
mpirun -np 7 ./par.exe 500 test_par.txt
echo "num_threads = 8"
mpirun -np 8 ./par.exe 500 test_par.txt
echo "num_threads = 9"
mpirun -np 9 ./par.exe 500 test_par.txt
echo "num_threads = 10"
mpirun -np 10 ./par.exe 500 test_par.txt
printf "\n"

echo "Try 750*750 matrix: "
echo "num_threads = 1"
mpirun -np 1 ./par.exe 750 test_par.txt
echo "num_threads = 2"
mpirun -np 2 ./par.exe 750 test_par.txt
echo "num_threads = 3"
mpirun -np 3 ./par.exe 750 test_par.txt
echo "num_threads = 4"
mpirun -np 4 ./par.exe 750 test_par.txt
echo "num_threads = 5"
mpirun -np 5 ./par.exe 750 test_par.txt
echo "num_threads = 6"
mpirun -np 6 ./par.exe 750 test_par.txt
echo "num_threads = 7"
mpirun -np 7 ./par.exe 750 test_par.txt
echo "num_threads = 8"
mpirun -np 8 ./par.exe 750 test_par.txt
echo "num_threads = 9"
mpirun -np 9 ./par.exe 750 test_par.txt
echo "num_threads = 10"
mpirun -np 10 ./par.exe 750 test_par.txt
printf "\n"

echo "Try 1000*1000 matrix: "
echo "num_threads = 1"
mpirun -np 1 ./par.exe 1000 test_par.txt
echo "num_threads = 2"
mpirun -np 2 ./par.exe 1000 test_par.txt
echo "num_threads = 3"
mpirun -np 3 ./par.exe 1000 test_par.txt
echo "num_threads = 4"
mpirun -np 4 ./par.exe 1000 test_par.txt
echo "num_threads = 5"
mpirun -np 5 ./par.exe 1000 test_par.txt
echo "num_threads = 6"
mpirun -np 6 ./par.exe 1000 test_par.txt
echo "num_threads = 7"
mpirun -np 7 ./par.exe 1000 test_par.txt
echo "num_threads = 8"
mpirun -np 8 ./par.exe 1000 test_par.txt
echo "num_threads = 9"
mpirun -np 9 ./par.exe 1000 test_par.txt
echo "num_threads = 10"
mpirun -np 10 ./par.exe 1000 test_par.txt
printf "\n"

rm -f test_par.txt
