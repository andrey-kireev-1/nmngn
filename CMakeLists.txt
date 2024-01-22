cmake_minimum_required(VERSION 3.26)
project(nmngn)

set(CMAKE_CXX_STANDARD 17)

add_executable(nmngn
        mpi/par_mpi.cpp
        par.cpp
        mpi/seq.cpp)
