#include <thread>
#include <iostream>
#include <cmath>
#include <chrono>
#include <cstddef>

#define N 1000 
#define MAX 100

const int num_threads = 8;

void multMatrix(int **mtx1, int **mtx2, int **res_mtx, int thread_counter, int thread_id) {

    for (int i = 0; i < N; i++) {

        if (i % thread_counter != thread_id)
            continue;

        for (int j = 0; j < N; j++) {
            res_mtx[i][j] = 0;
            for (int k = 0; k < N; k++) {
                res_mtx[i][j] += mtx1[i][k] * mtx2[k][j];
            }
        }
    }
}

int main() {

    int **matrix1   = new int*[N];
    int **matrix2   = new int*[N];
    int **matrixRes = new int*[N];

    for (int i = 0; i < N; i++) {
        matrix1[i]   = new int[N];
        matrix2[i]   = new int[N];
        
        for (int j = 0; j < N; j++) {
            matrix1[i][j] = rand() % MAX;
            matrix2[i][j] = rand() % MAX;
        }
        matrixRes[i] = new int[N];
    }

    std::thread threads[num_threads];

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < num_threads; i++)
        threads[i] = std::thread(multMatrix, matrix1, matrix2, matrixRes, num_threads, i);

    for (int i = 0; i < num_threads; i++)
        if (threads[i].joinable())
            threads[i].join();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << duration.count() / 1000.0 << " seconds" << std::endl;


    return 0;
}
