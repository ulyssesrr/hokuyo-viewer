#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T18:12:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hokuyo-viewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hokuyoreaderthread.cpp \
    hokuyographicsscene.cpp

HEADERS  += mainwindow.h \
    hokuyoreaderthread.h \
    hokuyographicsscene.h

FORMS    += mainwindow.ui
