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
<<<<<<< HEAD
    statusbar.cpp \
    push_button.cpp \
    tool_button.cpp
=======
    statusbar.cpp
>>>>>>> remotes/QtDirectUI/master

HEADERS  += mainwindow.h \
    contentwidget.h \
    statusbar.h \
<<<<<<< HEAD
    headerbar.h \
    push_button.h \
    tool_button.h
=======
    headerbar.h
>>>>>>> remotes/QtDirectUI/master

RESOURCES += \
    qtdirectui.qrc
