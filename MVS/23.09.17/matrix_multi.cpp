#include <iostream>
#include <vector>
#include <chrono>

using namespace std;


void transpose(int ** M, int n)
{
    for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < n / 2; ++j) {
            swap(M[i][j], M[j][i]);
        }
    }
}

int ** makeMatrix(int n)
{
    int ** M = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; ++i) {
        M[i] = (int *)malloc(sizeof(int) * n);
    }
    return M;
}

void fillMatrix(int ** M, int n)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            M[i][j] = rand() % 100;
        }
    }
}

void deleteMatrix(int ** M, int n)
{
    for (int i = 0; i < n; ++i) {
        free(M[i]);
    }
    free(M);
}
void f1(int ** A, int ** B, int ** C, int n)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int s = 0;
            for (int k = 0; k < n; ++k) {
                s += A[i][k] * B[k][j];
            }
            C[i][j] = s;
        }
    }
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "size = " << n << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0 <<std::endl;
}

void f2(int ** A, int ** B, int ** C, int n)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    transpose(C, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int s = 0;
            for (int k = 0; k < n; ++k) {
                s += A[i][k] * B[j][k];
            }
            C[i][j] = s;
        }
    }
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "size = " << n << endl;
    std::cout << "transpose time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0 <<std::endl;
}

int main()
{
    for (int size = 1024; size <= 1025; ++size) {
        int ** A = makeMatrix(size);
        int ** B = makeMatrix(size);
        int ** C = makeMatrix(size);
        fillMatrix(A, size);
        fillMatrix(B, size);
        f1(A, B, C, size);
        f2(A, B, C, size);
        //deleteMatrix(A, size);
        //deleteMatrix(B, size);
        //deleteMatrix(C, size);
    }
    return 0;
}
