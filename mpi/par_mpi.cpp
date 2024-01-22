#include <iostream>
#include <cstdlib>
#include <random>
#include <fstream>
#include <chrono>
#include </usr/lib/x86_64-linux-gnu/openmpi/include/mpi.h>

using namespace std;
using namespace std::chrono;

const int number_of_experiments = 4;

int rank_proc, size_proc;
const string separator_elem = ",";
const string separator_line = ";";

char *const b_tmp = (char*) "B_tmp.txt";
char *const c_tmp = (char*) "C_tmp.txt";
char *const d_tmp = (char*) "D_tmp.txt";
char *const e_tmp = (char*) "E_tmp.txt";
char *const i_tmp = (char*) "I_tmp.txt";

double rnd() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dis(0, 100);

    double random_double = dis(gen);
    return random_double;
}

void printMatrix(int n, double*& matrix){
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            cout << matrix[i*n + j] << "\t";
        }
        cout << endl;
    }
}

void create1DiagMatrix(int n, double*& matrix){
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if (i==j) {
                matrix[i*n + j] = 1;
            }
            else {
                matrix[i*n + j] = 0;
            }
        }
    }
}

void createFull1Matrix(int n, double*& matrix){
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            matrix[i*n + j] = 1;
        }
    }
}

void createRandom5DiagMatrix(int n, double*& matrix){
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if (i==j || i==j+1 || i==j-1 || i==j+2 || i==j-2) {
                matrix[i*n + j] = rnd();
            }
            else {
                matrix[i*n + j] = 0;
            }
        }
    }
}

void multiplyMatrix(int n, double*& a, double*& b, double*& c) {
    int part = n / size_proc;
    int cutted_n = size_proc * part;
    int ost = n - cutted_n;

    double *tmp{new double[n * n]{}};

    for (int i = rank_proc * part; i < (rank_proc + 1) * part; i++) {
        for (int j = 0; j < n; ++j) {
            tmp[i * n + j] = 0.0;
            for (int k = 0; k < n; ++k) {
                tmp[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allgather(&(tmp[rank_proc * part * n]), part * n, MPI_DOUBLE, c, part * n, MPI_DOUBLE, MPI_COMM_WORLD);
    free(tmp);

    if (ost != 0) {
        for (int i = size_proc * part; i < n; i++) {
            for (int j = 0; j < n; ++j) {
                c[i * n + j] = 0.0;
                for (int k = 0; k < n; ++k) {
                    c[i * n + j] += a[i * n + k] * b[k * n + j];
                }
            }
        }
    }
}

void sumMatrix(int n, double*& a, double*& b, double* c) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i*n + j] = a[i*n + j] + b[i*n + j];
        }
    }
}

void deleteFile (char* filename) {
    remove(filename);
}

void truncateFile (char* filename) {
    ofstream file(filename, ios::out | ios::trunc);
    file.close();
}

void saveMatrix(char* filename, int n, const string& s_elem, const string& s_line, double*& matrix){
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        int i, j;
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                file << matrix[i*n + j];
                if (j+1 != n) {
                    file << s_elem;
                }
            }
            if (i+1 != n) {
                file << s_line;
            }
        }
        file << "\n";
        file.close();
    } else {
        cout << "Error open file" << endl;
    }
}

void loadMatrix(char* filename, int n, double*& matrix){
    string line;
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                file >> matrix[i*n + j];
            }
        }
    }
    file.close();
}

long experiment(int n, char* filename) {
    MPI_Comm_rank (MPI_COMM_WORLD, &rank_proc);        /* get current process id */
    MPI_Comm_size (MPI_COMM_WORLD, &size_proc);

    double* matrixA{ new double[n * n] {} };
    double* matrixB{ new double[n * n] {} };
    double* matrixC{ new double[n * n] {} };
    double* matrixD{ new double[n * n] {} };
    double* matrixE{ new double[n * n] {} };
    double* matrixI{ new double[n * n] {} };
    double* matrixBC{ new double[n * n] {} };
    double* matrixDE{ new double[n * n] {} };
    double* matrixBCDE{ new double[n * n] {} };

    if (rank_proc == 0) {
        truncateFile(filename);

        deleteFile(b_tmp);
        deleteFile(c_tmp);
        deleteFile(d_tmp);
        deleteFile(e_tmp);
        deleteFile(i_tmp);

        createRandom5DiagMatrix(n, matrixB);
        createRandom5DiagMatrix(n, matrixC);
        createRandom5DiagMatrix(n, matrixD);
        create1DiagMatrix(n, matrixI);
        createFull1Matrix(n, matrixE);

        saveMatrix(b_tmp, n, " ", "\n", matrixB);
        saveMatrix(c_tmp, n, " ", "\n", matrixC);
        saveMatrix(d_tmp, n, " ", "\n", matrixD);
        saveMatrix(e_tmp, n, " ", "\n", matrixI);
        saveMatrix(i_tmp, n, " ", "\n", matrixE);
        MPI_Barrier(MPI_COMM_WORLD);
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
        loadMatrix(b_tmp, n, matrixB);
        loadMatrix(c_tmp, n, matrixC);
        loadMatrix(d_tmp, n, matrixD);
        loadMatrix(e_tmp, n, matrixI);
        loadMatrix(i_tmp, n, matrixE);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    long count_mcs = 0;
    auto startTime = high_resolution_clock::now();
    // Parallel block
    multiplyMatrix(n, matrixB, matrixC, matrixBC);
    multiplyMatrix(n, matrixD, matrixE, matrixDE);

    if (rank_proc == 0) {
        sumMatrix(n, matrixBC, matrixDE, matrixBCDE);
        sumMatrix(n, matrixBCDE, matrixI, matrixA);

        auto endTime = high_resolution_clock::now();
        auto searchTime = duration_cast<microseconds>(endTime - startTime);
        count_mcs = searchTime.count();

        saveMatrix(filename, n, separator_elem, separator_line, matrixB);
        saveMatrix(filename, n, separator_elem, separator_line, matrixC);
        saveMatrix(filename, n, separator_elem, separator_line, matrixD);
        saveMatrix(filename, n, separator_elem, separator_line, matrixI);
        saveMatrix(filename, n, separator_elem, separator_line, matrixE);
        saveMatrix(filename, n, separator_elem, separator_line, matrixA);
    }
    free(matrixA);
    free(matrixB);
    free(matrixC);
    free(matrixD);
    free(matrixE);
    free(matrixI);
    free(matrixBC);
    free(matrixDE);
    free(matrixBCDE);
    return count_mcs;
}

int main(int argc, char* argv[]) {
    int n = 0;
    n = atoi(argv[1]);

    char* filename = argv[2];
    MPI_Init (&argc, &argv);

    long average_mcs = 0;
    for (int i = 1; i <= number_of_experiments; ++i) {
        long count_mcs = experiment(n, filename);
        if (rank_proc == 0) {
            // cout << "Search time (mcs) of " << i << " experiments: " << count_mcs << endl;
            average_mcs += count_mcs;
        }
    }

    if (rank_proc == 0) {
        average_mcs = average_mcs / number_of_experiments;
        cout << "Average Search time (mcs): " << average_mcs << endl;
    }

    MPI_Finalize();
    return 0;
}