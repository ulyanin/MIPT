//
// Created by ulyanin on 07.10.17.
//

#ifndef INC_07_10_2017_HELPER_H
#define INC_07_10_2017_HELPER_H

#include <QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>


class Helper: public QThread
{
    Q_OBJECT
public:
    Helper();

    virtual ~Helper() {};

    void stop();

protected:
    void run();

private:
    volatile bool stopped;
    QMutex mutex;
    QWaitCondition cond;
};


#endif //INC_07_10_2017_HELPER_H
