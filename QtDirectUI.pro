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
    statusbar.cpp \
    push_button.cpp \
    tool_button.cpp \
    contentwidget.cpp

HEADERS  += mainwindow.h \
    contentwidget.h \
    statusbar.h \
    headerbar.h \
    push_button.h \
    tool_button.h

RESOURCES += \
    qtdirectui.qrc
