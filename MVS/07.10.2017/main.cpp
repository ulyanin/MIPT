#include <iostream>
#include <QThread>
#include <memory>
#include <unistd.h>
#include <thread>
#include "Helper.h"

int main()
{
    Helper * h = new Helper();
    h->start();
    usleep(1000);
//    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    h->stop();
    h->quit();
    h->wait();
    delete h;
    return 0;
}