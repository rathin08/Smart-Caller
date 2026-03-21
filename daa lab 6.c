#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_time() {
    return (double)clock() / CLOCKS_PER_SEC;
}

int **allocate(int n) {
    int **m = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        m[i] = (int *)malloc(n * sizeof(int));
    return m;
}

void free_matrix(int **m, int n) {
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void fill_random(int **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = rand() % 10;
}

void add(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void standard(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int **A11 = allocate(k);
    int **A12 = allocate(k);
    int **A21 = allocate(k);
    int **A22 = allocate(k);
    int **B11 = allocate(k);
    int **B12 = allocate(k);
    int **B21 = allocate(k);
    int **B22 = allocate(k);
    int **C11 = allocate(k);
    int **C12 = allocate(k);
    int **C21 = allocate(k);
    int **C22 = allocate(k);
    int **M1 = allocate(k);
    int **M2 = allocate(k);
    int **M3 = allocate(k);
    int **M4 = allocate(k);
    int **M5 = allocate(k);
    int **M6 = allocate(k);
    int **M7 = allocate(k);
    int **T1 = allocate(k);
    int **T2 = allocate(k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }

    add(A11, A22, T1, k);
    add(B11, B22, T2, k);
    strassen(T1, T2, M1, k);

    add(A21, A22, T1, k);
    strassen(T1, B11, M2, k);

    subtract(B12, B22, T2, k);
    strassen(A11, T2, M3, k);

    subtract(B21, B11, T2, k);
    strassen(A22, T2, M4, k);

    add(A11, A12, T1, k);
    strassen(T1, B22, M5, k);

    subtract(A21, A11, T1, k);
    add(B11, B12, T2, k);
    strassen(T1, T2, M6, k);

    subtract(A12, A22, T1, k);
    add(B21, B22, T2, k);
    strassen(T1, T2, M7, k);

    add(M1, M4, T1, k);
    subtract(T1, M5, T2, k);
    add(T2, M7, C11, k);

    add(M3, M5, C12, k);
    add(M2, M4, C21, k);

    subtract(M1, M2, T1, k);
    add(T1, M3, T2, k);
    add(T2, M6, C22, k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }

    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(C11, k); free_matrix(C12, k); free_matrix(C21, k); free_matrix(C22, k);
    free_matrix(M1, k); free_matrix(M2, k); free_matrix(M3, k); free_matrix(M4, k);
    free_matrix(M5, k); free_matrix(M6, k); free_matrix(M7, k);
    free_matrix(T1, k); free_matrix(T2, k);
}

int main() {
    srand(time(NULL));
    int sizes[] = {32, 64, 128, 111256};
    int count = 4;

    for (int s = 0; s < count; s++) {
        int n = sizes[s];
        int **A = allocate(n);
        int **B = allocate(n);
        int **C1 = allocate(n);
        int **C2 = allocate(n);

        fill_random(A, n);
        fill_random(B, n);

        double start = get_time();
        standard(A, B, C1, n);
        double end = get_time();
        double t_standard = end - start;

        start = get_time();
        strassen(A, B, C2, n);
        end = get_time();
        double t_strassen = end - start;

        printf("n = %d\n", n);
        printf("Standard Time: %f\n", t_standard);
        printf("Strassen Time: %f\n\n", t_strassen);

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C1, n);
        free_matrix(C2, n);
    }

    return 0;
}

