import sys
import numpy as np
import math

if __name__ == "__main__":
    filename = sys.argv[1]
    f = open(filename, 'r')

    B = np.matrix(f.readline())
    C = np.matrix(f.readline())
    D = np.matrix(f.readline())
    I = np.matrix(f.readline())
    E = np.matrix(f.readline())
    A_res = np.matrix(f.readline())

    BC = np.matmul(B, C)
    DE = np.matmul(D, E)

    BCDE = BC + DE

    A_test = BCDE + I

    A_res = np.round(A_res, 2)
    A_test = np.round(A_test, 2)

    is_equal = True
    for i in range(0, len(A_res[0])):
        for j in range(0, len(A_res[0])):
            if math.fabs(A_res[i][j] - A_test[i][j]) > 0.1:
                is_equal = False

    print(is_equal)

