#ifndef HOKUYOREADERTHREAD_H
#define HOKUYOREADERTHREAD_H

#include <QThread>


extern "C" {
    #include "hokuyourg.h"
};

#define HOKUYO_READ_BUFFER_SIZE 16384


class HokuyoReaderThread : public QThread
{
    Q_OBJECT
public:
    explicit HokuyoReaderThread(QObject *parent = 0);
protected:
    void run();
signals:
    void onErrorOpeningHokuyo();
    void onErrorInitializingHokuyo();
    void onErrorStartingHokuyoContinuousRead();
    void onScanReading(HokuyoRangeReading* value);

public slots:

private:
    HokuyoURG* hokuyo;
    bool running = true;
};

#endif // HOKUYOREADERTHREAD_H
