//
// Created by ulyanin on 07.10.17.
//

#ifndef INC_07_10_2017_HELPER_H
#define INC_07_10_2017_HELPER_H

#include <QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <iostream>

class MyObject : public QObject
{
Q_OBJECT
public slots:
    void MySlot()
    {
        std::cout << "slot called" << std::endl;
    }
};

class Thread1 : public QThread
{
Q_OBJECT
public:
    void run()
    {
        std::cout << "thread 1 started" << std::endl;
        for (int i = 0; i < 5; i++) {
            sleep(1);
            emit MySignal();
        }
    }
signals:
    void MySignal();
};

class Thread2 : public QThread
{
Q_OBJECT
public:
    void run()
    {
        std::cout << "thread 2 started" << std::endl;
        exec();
    }
};

#endif //INC_07_10_2017_HELPER_H
