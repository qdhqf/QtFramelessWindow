#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T22:25:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtDirectUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    headerbar.cpp \
    statusbar.cpp

HEADERS  += mainwindow.h \
    contentwidget.h \
    statusbar.h \
    headerbar.h

RESOURCES += \
    qtdirectui.qrc
