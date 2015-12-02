#ifndef HOKUYOREADERTHREAD_H
#define HOKUYOREADERTHREAD_H

#include <QThread>


class HokuyoReaderThread : public QThread
{
    Q_OBJECT
public:
    explicit HokuyoReaderThread(QObject *parent = 0);
protected:
    void run();
signals:
    void onScanReading(int value);
public slots:

};

#endif // HOKUYOREADERTHREAD_H
