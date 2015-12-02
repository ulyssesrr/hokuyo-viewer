#ifndef HOKUYOGRAPHICSSCENE_H
#define HOKUYOGRAPHICSSCENE_H

#include <QGraphicsScene>

class HokuyoGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    HokuyoGraphicsScene();
public slots:
    void setScanRanges(int value);
private:
    QVector<QGraphicsEllipseItem*> ellipses;
};

#endif // HOKUYOGRAPHICSSCENE_H
