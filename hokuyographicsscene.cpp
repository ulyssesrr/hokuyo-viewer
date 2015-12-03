#include "hokuyographicsscene.h"

#include <QtCore/qmath.h>
#include <QGraphicsView>
#include <QDebug>

#define MAX_SENSOR_RANGE 30000.0

#define ANGLE_STEP (2*M_PI/1440.0)

HokuyoGraphicsScene::HokuyoGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    /*for(int i = 0; i < 1080; i++) {
        this->ellipses.append(this->addEllipse(1, 1, 1, 1));
    }*/
    this->setItemIndexMethod(QGraphicsScene::NoIndex);

    this->text = new QGraphicsTextItem;
    this->text->setPos(0,0);
    this->text->setPlainText("");
    this->addItem(this->text);
}

void HokuyoGraphicsScene::setScanRanges(HokuyoRangeReading* reading)
{
    int n_ranges = reading->n_ranges;

    if (this->lastTimestamp > 0) {
        int timestampDiff = reading->timestamp - this->lastTimestamp;
        float scanPerSec = 1000.0 / timestampDiff;
        this->text->setPlainText(QString::number(scanPerSec) + QString(" scans/sec"));
    }
    this->lastTimestamp = reading->timestamp;


    // allocate ellipses (if needed)
    for (int i = this->ellipses.size(); i < n_ranges; i++) {
        QGraphicsEllipseItem* ellipse = this->addEllipse(1, 1, 1, 1);
        ellipses.append(ellipse);
    }

    QGraphicsView* view = (QGraphicsView*) this->parent();
    const qreal l = qMin(view->height(), view->width())/2;

    for (int i = 0; i < n_ranges; i++) {

        qreal range = reading->ranges[i];
        //qreal range = MAX_SENSOR_RANGE; // testing

        qreal relRange = range / MAX_SENSOR_RANGE;

        qreal angle = i*ANGLE_STEP + 3*M_PI/4;

        qreal x = qCos(angle) * relRange * l;
        qreal y = qSin(angle) * relRange * l;

        //qDebug() <<  "L: " << l;

        ellipses[i]->setRect(x, y, 1, 1);
    }
}
