#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include "pthread.h"
#include <unistd.h>

pthread_spinlock_t lock;
pthread_mutex_t mutex;
using namespace std::chrono_literals;

int globalVariable = 10;
int stepNumber = (int)(2e7);
const int MOD = (int)(1e9) + 7;
const int CPU_HARDWARE_THREAD_NUMBER = std::thread::hardware_concurrency();
int defaultThreadNum = 8;

void fun_spin(int steps, int threadNumber)
{
    int sum = 0;
    for (int i = 0; i < steps; ++i) {
        if (pthread_spin_trylock(&lock)) {
            globalVariable = (globalVariable + 1) % MOD;
            sum = (sum + globalVariable++) % MOD;
            pthread_spin_unlock(&lock);
        } else {
            --i;
            if (threadNumber > CPU_HARDWARE_THREAD_NUMBER) {
                std::this_thread::yield();
            }
        }
    }
}

void fun_mutex(int steps, int threadNumber)
{
    int sum = 0;
    for (int i = 0; i < steps; ++i) {
        if (pthread_mutex_trylock(&mutex)) {
//            pthread_mutex_lock(&mutex);
            globalVariable = (globalVariable + 1) % MOD;
            sum = (sum + globalVariable++) % MOD;
            pthread_mutex_unlock(&mutex);
        } else {
            --i;
        }
    }
}

void spinWork(int threadNum = defaultThreadNum)
{

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::vector<std::thread> threads;
    for (int i = 0; i < threadNum; ++i) {
        threads.emplace_back(fun_spin, stepNumber / threadNum, threadNum);
    }
    for (int i = 0; i < threadNum; ++i) {
        threads[i].join();
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "SPIN time difference = " << timeElapsed / (1e6) << std::endl;
}

void mutexWork(int threadNum = defaultThreadNum)
{

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::vector<std::thread> threads;
    for (int i = 0; i < threadNum; ++i) {
        threads.emplace_back(fun_mutex, stepNumber / threadNum, threadNum);
    }
    for (int i = 0; i < threadNum; ++i) {
        threads[i].join();
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "MUTEX time difference = " << timeElapsed / (1e6) <<std::endl;
}


void init()
{
    int ret1 = pthread_spin_init(&lock, NULL);
    int ret2 = pthread_mutex_init(&mutex, nullptr);
}

int main()
{
    init();
    for (int threadNum = 2; threadNum <= 16; threadNum *= 2) {
        std::cout << "threads: " << threadNum << std::endl;
        spinWork(threadNum);
        mutexWork(threadNum);
    }

    return 0;
}