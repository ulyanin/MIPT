//
// Created by ulyanin on 07.10.17.
//

#include <iostream>
#include <mutex>
#include "Helper.h"


Helper::Helper()
    : stopped(false)
{

}

void Helper::run()
{
//    while (!stopped) {
//        QMutexLocker lock(&mutex);
//        if (stopped) {
//            std::cout << "..." << std::endl;
//            stopped = true;
//            break;
//        }
//        std::cout << "Thread is wating" << std::endl;
//        yieldCurrentThread();
//    }
    QMutexLocker lock(&mutex);
    std::cout << "Thread is wating" << std::endl;
    cond.wait(&mutex);
    std::cout << "Thread is stopping" << std::endl;
}

void Helper::stop()
{
//    QMutexLocker lock(&mutex);
//    stopped = true;
    cond.wakeAll();
}
