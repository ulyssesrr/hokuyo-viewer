#ifndef HOKUYOGRAPHICSSCENE_H
#define HOKUYOGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

class HokuyoGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit HokuyoGraphicsScene(QObject *parent = 0);
public slots:
    void setScanRanges(short* value);
private:
    QVector<QGraphicsEllipseItem*> ellipses;
};

#endif // HOKUYOGRAPHICSSCENE_H
