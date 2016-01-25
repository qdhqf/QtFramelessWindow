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
    titlebar.cpp

HEADERS  += mainwindow.h \
    titlebar.h \
    toolbar.h \
    contentwidget.h \
    statusbar.h

RESOURCES += \
    qtdirectui.qrc
