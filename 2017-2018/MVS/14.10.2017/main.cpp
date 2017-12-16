#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include "lock_free_stack.h"

using namespace std;

const int N = 50000;
int producers = 3;
int consumers = 3;

void f(int thread_num, lock_free_stack<int> &q)
{
    cout << "push " << N * consumers << endl;
    for (int i = 0; i < N * consumers; ++i) {
        q.push(i);
        cout << "push " << i << endl;
    }
}
void f2(int thread_num, lock_free_stack<int> &q)
{
    cout << "pop " << N * producers << endl;
    for (int i = 0; i < N * producers; ++i) {
        int val = -1;
        bool f = q.pop(val);
        cout << "pop (" << f;
        cout << ") " << val << endl;
    }
}

int main()
{
    lock_free_stack<int> stack;
    std::vector<std::thread> threads;
    for (int i = 0; i < producers; ++i) {
//        f2(i, queue);
        threads.emplace_back(f, i, std::ref(stack));
    }
//    sleep(1);
    for (int i = 0; i < consumers; ++i) {
//        f(i, queue);
        threads.emplace_back(f2, i, std::ref(stack));
    }
    cout << "s" << endl;
    sleep(2);
    cout << "join" << endl;
    for (size_t i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
    cout << "endjoin" << endl;
    return 0;
}