#ifndef HOKUYOGRAPHICSSCENE_H
#define HOKUYOGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include <hokuyoaist/hokuyoaist.h>

//extern "C" {
//    #include "hokuyourg.h"
//};

class HokuyoGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit HokuyoGraphicsScene(QObject *parent = 0);
public slots:
    void setScanRanges(hokuyoaist::ScanData* value);
private:
    QVector<QGraphicsEllipseItem*> ellipses;
    QGraphicsTextItem* text;
    unsigned int lastTimestamp = 0;
};

#endif // HOKUYOGRAPHICSSCENE_H
