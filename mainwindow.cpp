#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showErrorOpeningHokuyo()
{
    QMessageBox messageBox;
    messageBox.critical(this, "error", "Hokuyo open() failed.");
}

void MainWindow::showErrorInitializingHokuyo()
{
    QMessageBox messageBox;
    messageBox.critical(this, "error", "Hokuyo init() failed.");
}

void MainWindow::showErrorStartingHokuyoContinuousRead()
{
    QMessageBox messageBox;
    messageBox.critical(this, "error", "Hokuyo hokuyo_startContinuous() failed.");
}
