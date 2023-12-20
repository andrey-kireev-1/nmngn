#include <iostream>
#include <cstdlib>
#include <random>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

double rnd() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dis(0, 100);

    double random_double = dis(gen);
    return random_double;
}

void create1DiagMatrix(int n, double** matrix){
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if (i==j) {
                matrix[i][j] = 1;
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
}

void createFull1Matrix(int n, double** matrix){
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            matrix[i][j] = 1;
        }
    }
}

void createRandom5DiagMatrix(int n, double** matrix){
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if (i==j || i==j+1 || i==j-1 || i==j+2 || i==j-2) {
                matrix[i][j] = rnd();
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
}

void multiplyMatrix(int n, double** a, double** b, double** c) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void sumMatrix(int n, double** a, double** b, double** c) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void printMatrix(int n, double** matrix){
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void truncateFile (char* filename) {
    ofstream file(filename, ios::out | ios::trunc);
    file.close();
}

void saveMatrix(char* filename, int n, double** matrix){
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        int i, j;
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                file << matrix[i][j];
                if (j+1 != n) {
                    file << ",";
                }
            }
            if (i+1 != n) {
                file << ";";
            }
        }
        file << "\n";
        file.close();
    } else {
        cout << "Error open file" << endl;
    }
}

int main(int argc, char* argv[]) {
    int n = 0;
    n = atoi(argv[1]);

    char* filename = argv[2];
    truncateFile(filename);

    auto startTime = high_resolution_clock::now();

    double **matrixA;
    double **matrixB;
    double **matrixC;
    double **matrixD;
    double **matrixE;
    double **matrixI;
    double **matrixBC;
    double **matrixDE;
    double **matrixBCDE;
    matrixA = (double**)malloc( n * sizeof(double*) ) ;
    matrixB = (double**)malloc( n * sizeof(double*) ) ;
    matrixC = (double**)malloc( n * sizeof(double*) ) ;
    matrixD = (double**)malloc( n * sizeof(double*) ) ;
    matrixE = (double**)malloc( n * sizeof(double*) ) ;
    matrixI = (double**)malloc( n * sizeof(double*) ) ;
    matrixBC = (double**)malloc( n * sizeof(double*) ) ;
    matrixDE = (double**)malloc( n * sizeof(double*) ) ;
    matrixBCDE = (double**)malloc( n * sizeof(double*) ) ;
    for( int r = 0 ; r < n ; r++ )
    {
        matrixA[r] = (double*)malloc( n*sizeof(double) ) ;
        matrixB[r] = (double*)malloc( n*sizeof(double) ) ;
        matrixC[r] = (double*)malloc( n*sizeof(double) ) ;
        matrixD[r] = (double*)malloc( n*sizeof(double) ) ;
        matrixE[r] = (double*)malloc( n*sizeof(double) ) ;
        matrixI[r] = (double*)malloc( n*sizeof(double) ) ;
        matrixBC[r] = (double*)malloc( n*sizeof(double) ) ;
        matrixDE[r] = (double*)malloc( n*sizeof(double) ) ;
        matrixBCDE[r] = (double*)malloc( n*sizeof(double) ) ;
    }

    createRandom5DiagMatrix(n, matrixB);
    createRandom5DiagMatrix(n, matrixC);
    createRandom5DiagMatrix(n, matrixD);
    create1DiagMatrix(n, matrixI);
    createFull1Matrix(n, matrixE);

    multiplyMatrix(n, matrixB, matrixC, matrixBC);
    multiplyMatrix(n, matrixD, matrixE, matrixDE);
    sumMatrix(n, matrixBC, matrixDE, matrixBCDE);
    sumMatrix(n, matrixBCDE, matrixI, matrixA);

    auto endTime = high_resolution_clock::now();
    auto searchTime = duration_cast<microseconds>(endTime - startTime);
    printf("Search time (mcs): %ld", searchTime.count());

    saveMatrix(filename, n, matrixB);
    saveMatrix(filename, n, matrixC);
    saveMatrix(filename, n, matrixD);
    saveMatrix(filename, n, matrixI);
    saveMatrix(filename, n, matrixE);
    saveMatrix(filename, n, matrixA);

    return 0;
}