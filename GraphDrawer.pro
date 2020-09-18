QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphDrawer
TEMPLATE = app

SOURCES += main.cpp\
        GraphDrawer.cpp \
        krawedz.cpp \
        mainwindow.cpp \
        wierzcholek.cpp


HEADERS  += mainwindow.h \
         GraphDrawer.h \
         krawedz.h \
         wierzcholek.h

FORMS    += mainwindow.ui


