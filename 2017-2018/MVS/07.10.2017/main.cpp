#include <iostream>
#include <QThread>
#include <memory>
#include <unistd.h>
#include <thread>
#include <QtCore/QThreadPool>
#include <QtCore/QCoreApplication>
#include "Helper.h"

int main(int argc, char ** argv)
{
    QCoreApplication a(argc, argv);
    Thread1 th1;
    Thread2 th2;
    MyObject ob;
    QObject::connect(&th1, SIGNAL(MySignal()), &ob, SLOT(MySlot()));
    th2.start();
    ob.moveToThread(&th2);
    th1.start();
    th1.wait();
    th2.quit();
    th2.wait();
    return 0;
}