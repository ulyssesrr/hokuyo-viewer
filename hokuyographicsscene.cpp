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



    //reference arrow
    QFont font;
    font.setPixelSize(25);
    QGraphicsTextItem* arrow = this->addText("^", font);
    arrow->setPos(-10, -10);
    arrow->setDefaultTextColor(Qt::red);

    this->text = new QGraphicsTextItem;
    this->text->setPos(200, 200);
    this->text->setPlainText("");
    this->addItem(this->text);
}

void HokuyoGraphicsScene::setScanRanges(hokuyoaist::ScanData* reading)
{

    const unsigned int n_ranges = reading->ranges_length();
    //qDebug() << "Received ranges: " << n_ranges;

    if (this->lastTimestamp > 0) {
        int timestampDiff = reading->laser_time_stamp() - this->lastTimestamp;
        float scanPerSec = 1000.0 / timestampDiff;
        this->text->setPlainText(QString::number(scanPerSec) + QString(" scans/sec"));
    }
    this->lastTimestamp = reading->laser_time_stamp();
    //qDebug() << "this->lastTimestamp: " << this->lastTimestamp;


    // allocate ellipses (if needed)
    for (int i = this->ellipses.size(); i < n_ranges; i++) {
        QGraphicsEllipseItem* ellipse = this->addEllipse(1, 1, 1, 1);
        ellipses.append(ellipse);
    }

    QGraphicsView* view = (QGraphicsView*) this->parent();
    const qreal l = qMin(view->height(), view->width())/2;

    for (int i = 0; i < n_ranges; i++) {

        qreal range = reading->ranges()[i];

        //qreal range = MAX_SENSOR_RANGE; // testing

        qreal relRange = range / 3000;

        qreal angle = i*ANGLE_STEP + 3*M_PI/4;

        qreal x = qCos(angle) * relRange * l;
        qreal y = qSin(angle) * relRange * l;

        //qDebug() <<  "L: " << l;

        ellipses[i]->setRect(x, y, 1, 1);
    }

    delete reading;
}
