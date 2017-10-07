#include <iostream>
#include <QThread>
#include <memory>
#include <unistd.h>
#include <thread>
#include <QtCore/QThreadPool>
#include "Helper.h"

int main()
{
    Helper * h1 = new Helper();
    Helper * h2 = new Helper();
    QThreadPool::globalInstance()->setMaxThreadCount(2);
    QThreadPool::globalInstance()->start(h1);
    QThreadPool::globalInstance()->start(h2);
    QThreadPool::globalInstance()->waitForDone();
    return 0;
}