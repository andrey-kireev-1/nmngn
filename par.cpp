#include <chrono>
#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <random>
#include <fstream>
#include <cstring>

using namespace std;

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
    int i, j, k;
    #pragma omp parallel for private(i,j,k) shared(a,b,c)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = 0;
            for (k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void sumMatrix(int n, double** a, double** b, double** c) {
    int i, j;
    #pragma omp parallel for private(i,j) shared(a,b,c)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
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

void saveResult(char* filename, int n, int numThreads, double searchTime){
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << "Matrix size: " << n << ", Number threads: " << numThreads << ", Search Time (mcs): " << searchTime << "\n";
        file.close();
    } else {
        cout << "Error open file" << endl;
    }
}

void experiment(int n, char* filename) {
    int numThreads = 1;
    double searchTime = UINT32_MAX;
    double prevSearchTime = 0;
    do {
        double startTime = omp_get_wtime();

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
        omp_set_num_threads(numThreads);
        createRandom5DiagMatrix(n, matrixB);
        createRandom5DiagMatrix(n, matrixC);
        createRandom5DiagMatrix(n, matrixD);
        create1DiagMatrix(n, matrixI);
        createFull1Matrix(n, matrixE);

        prevSearchTime = searchTime;

        multiplyMatrix(n, matrixB, matrixC, matrixBC);
        multiplyMatrix(n, matrixD, matrixE, matrixDE);
        sumMatrix(n, matrixBC, matrixDE, matrixBCDE);
        sumMatrix(n, matrixBCDE, matrixI, matrixA);

        double endTime = omp_get_wtime();
        searchTime = endTime - startTime;

        saveResult(filename, n, numThreads, searchTime*1000000);

        for( int r = 0 ; r < n ; r++ )
        {
            free(matrixA[r]);
            free(matrixB[r]);
            free(matrixC[r]);
            free(matrixD[r]);
            free(matrixE[r]);
            free(matrixI[r]);
            free(matrixBC[r]);
            free(matrixDE[r]);
            free(matrixBCDE[r]);
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

        numThreads++;
    } while (searchTime < prevSearchTime);
}

void noExperiment(int n, char* filename) {
    double startTime = omp_get_wtime();

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
    omp_set_num_threads(3);
    createRandom5DiagMatrix(n, matrixB);
    createRandom5DiagMatrix(n, matrixC);
    createRandom5DiagMatrix(n, matrixD);
    create1DiagMatrix(n, matrixI);
    createFull1Matrix(n, matrixE);

    multiplyMatrix(n, matrixB, matrixC, matrixBC);
    multiplyMatrix(n, matrixD, matrixE, matrixDE);
    sumMatrix(n, matrixBC, matrixDE, matrixBCDE);
    sumMatrix(n, matrixBCDE, matrixI, matrixA);

    double endTime = omp_get_wtime();
    double searchTime = endTime - startTime;
    printf("Search time (mcs): %f", searchTime*1000000);

    saveMatrix(filename, n, matrixB);
    saveMatrix(filename, n, matrixC);
    saveMatrix(filename, n, matrixD);
    saveMatrix(filename, n, matrixI);
    saveMatrix(filename, n, matrixE);
    saveMatrix(filename, n, matrixA);

    for( int r = 0 ; r < n ; r++ )
    {
        free(matrixA[r]);
        free(matrixB[r]);
        free(matrixC[r]);
        free(matrixD[r]);
        free(matrixE[r]);
        free(matrixI[r]);
        free(matrixBC[r]);
        free(matrixDE[r]);
        free(matrixBCDE[r]);
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
}

int main(int argc, char* argv[]) {
    int n = 0;
    n = atoi(argv[1]);

    char* filename = argv[2];
    truncateFile(filename);

    char* mode = argv[3];

    if (strcmp(mode, "experiment") == 0) {
        experiment(n, filename);
    } else if (strcmp(mode, "no_experiment") == 0) {
        noExperiment(n, filename);
    } else {
        printf("Select correct mode!");
        return 1;
    }

    return 0;
}