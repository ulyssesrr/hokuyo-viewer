#include "hokuyoreaderthread.h"

HokuyoReaderThread::HokuyoReaderThread(QObject *parent) : QThread(parent)
{

}

void HokuyoReaderThread::run()
{
    int i = 0;
    while (1) {
        msleep(25);
        emit onScanReading(NULL);
    }
}
