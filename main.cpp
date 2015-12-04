#include "mainwindow.h"
#include <QApplication>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointF>
#include <QVector>
#include <QGraphicsEllipseItem>

#include <QGLWidget>

#include "hokuyographicsscene.h"
#include "hokuyoreaderthread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();


    // Create a view, put a scene in it and add tiny circles
    // in the scene
    QGraphicsView* view = new QGraphicsView(&w);
    view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DirectRendering)));
    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    view->update();

    HokuyoGraphicsScene* scene = new HokuyoGraphicsScene(view);

    HokuyoReaderThread hokuyoReaderThread;

    QObject::connect(&hokuyoReaderThread, SIGNAL(onScanReading(hokuyoaist::ScanData*)),
                         scene, SLOT(setScanRanges(hokuyoaist::ScanData*)));


    hokuyoReaderThread.start();
    view->setScene(scene);

    w.setCentralWidget(view);


    // Show the view
    w.show();

    return a.exec();
}
