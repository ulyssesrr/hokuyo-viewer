#include "hokuyoreaderthread.h"

#include <QDebug>
#include <QMessageBox>
#include <QApplication>

HokuyoReaderThread::HokuyoReaderThread(QObject *parent) : QThread(parent)
{

}

void HokuyoReaderThread::run()
{
    HokuyoURG h;
    this->hokuyo = &h;
    int ret = hokuyo_open(this->hokuyo, " /dev/ttyACM0");
    if (ret > 0) {
        ret = hokuyo_init(this->hokuyo);
        if (ret > 0) {
            ret = hokuyo_startContinuous(this->hokuyo, 0, 1079, 0);
            if (ret > 0) {
                char buf[HOKUYO_READ_BUFFER_SIZE];

                int i = 0;
                while (this->running) {
                    hokuyo_readPacket(this->hokuyo, buf, HOKUYO_READ_BUFFER_SIZE, 10);
                    HokuyoRangeReading hokuyoReading;
                    hokuyo_parseReading(&hokuyoReading, buf);
                    emit onScanReading(&hokuyoReading);
                }

                qDebug() << "Closing hokuyo...";
                hokuyo_close(this->hokuyo);
            }
            else {
                qDebug() << "Hokuyo hokuyo_startContinuous() failed.";
                emit onErrorStartingHokuyoContinuousRead();
            }
        }
        else {
            qDebug() << "Hokuyo init() failed.";
            emit onErrorInitializingHokuyo();
        }
    }
    else {
        qDebug() << "Hokuyo open() failed.";
        emit onErrorOpeningHokuyo();
//        int k = 1000;
//        while (1) {
//            HokuyoRangeReading hokuyoReading;
//            hokuyoReading.n_ranges = 1080;
//            hokuyoReading.timestamp = (k-1000)/100 * 25;
//            for (int i = 0; i < hokuyoReading.n_ranges; i++) {
//                hokuyoReading.ranges[i] = k;
//            }
//            k += 100;
//            emit onScanReading(&hokuyoReading);

//            msleep(25);
//        }
    }
}
