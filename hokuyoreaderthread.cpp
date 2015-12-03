#include "hokuyoreaderthread.h"

#include <QDebug>
#include <QMessageBox>

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
                while (1) {
                    hokuyo_readPacket(this->hokuyo, buf, HOKUYO_READ_BUFFER_SIZE, 10);
                    HokuyoRangeReading hokuyoReading;
                    hokuyo_parseReading(&hokuyoReading, buf);
                    emit onScanReading(&hokuyoReading);
                }
            }
            else {
                qDebug() << "Hokuyo hokuyo_startContinuous() failed.";
                QMessageBox messageBox;
                messageBox.critical(0, "error", "Hokuyo hokuyo_startContinuous() failed.");
            }
        }
        else {
            qDebug() << "Hokuyo init() failed.";
            QMessageBox messageBox;
            messageBox.critical(0, "error", "Hokuyo init() failed.");
        }
    }
    else {
        qDebug() << "Hokuyo open() failed.";
        QMessageBox messageBox;
        messageBox.critical(0, "error", "Hokuyo open() failed.");
    }
}
