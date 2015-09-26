#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "mType.h"

class AIThread : public QThread
{
    Q_OBJECT
public:
    bool stop;
    explicit AIThread(const ThreadArgs mArgs,QObject *parent = 0);
    void run();
    ThreadReturn result;
signals:

public slots:

private:
    const ThreadArgs Args;
};

#endif // MYTHREAD_H
