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
}

void HokuyoGraphicsScene::setScanRanges(HokuyoRangeReading* reading)
{
    int n_ranges = reading->n_ranges;

    // allocate ellipses (if needed)
    for (int i = this->ellipses.size(); i < n_ranges; i++) {
        ellipses.append(this->addEllipse(1, 1, 1, 1));
    }

    QGraphicsView* view = (QGraphicsView*) this->parent();
    const qreal l = qMin(view->height(), view->width())/2;

    for (int i = 0; i < n_ranges; i++) {

        qreal range = reading->ranges[i];
        qreal relRange = range / MAX_SENSOR_RANGE;

        qreal angle = i*ANGLE_STEP + 3*M_PI/4;

        qreal x = qCos(angle) * relRange * l;
        qreal y = qSin(angle) * relRange * l;

        //qDebug() <<  "L: " << l;

        ellipses[i]->setRect(x, y, 1, 1);
    }
}
