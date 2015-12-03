#ifndef HOKUYOGRAPHICSSCENE_H
#define HOKUYOGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

extern "C" {
    #include "hokuyourg.h"
};

class HokuyoGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit HokuyoGraphicsScene(QObject *parent = 0);
public slots:
    void setScanRanges(HokuyoRangeReading* value);
private:
    QVector<QGraphicsEllipseItem*> ellipses;
};

#endif // HOKUYOGRAPHICSSCENE_H
