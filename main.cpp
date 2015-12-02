#include "mainwindow.h"
#include <QApplication>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointF>
#include <QVector>
#include <QGraphicsEllipseItem>

#include "hokuyographicsscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();


    // Create a view, put a scene in it and add tiny circles
    // in the scene
    QGraphicsView* view = new QGraphicsView();
    HokuyoGraphicsScene* scene = new HokuyoGraphicsScene();

    QObject::connect(&a, SIGNAL(valueChanged(int)),
                         &scene, SLOT(setValue(int)));


    view->setScene(scene);


    // Show the view
    view->show();

    return a.exec();
}
