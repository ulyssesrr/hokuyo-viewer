#ifndef HOKUYOREADERTHREAD_H
#define HOKUYOREADERTHREAD_H

#include <QThread>

#include <hokuyoaist/hokuyoaist.h>

//extern "C" {
//    #include "hokuyourg.h"
//};

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
    void onScanReading(hokuyoaist::ScanData* value);

public slots:

private:
};

#endif // HOKUYOREADERTHREAD_H
