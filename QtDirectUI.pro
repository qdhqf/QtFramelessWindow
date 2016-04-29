#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T22:25:24
#
#-------------------------------------------------

QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TransInsight
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    headerbar.cpp \
    statusbar.cpp \
    tabwidget.cpp \
    pushbutton.cpp \
    toolbutton.cpp \
    mainmenu.cpp \
    database.cpp \
    framelesshelper.cpp \
    nodeitem.cpp \
    nettopoview.cpp \
    nettoposcene.cpp \
    portlinkitem.cpp

HEADERS  += mainwindow.h \
    statusbar.h \
    headerbar.h \
    tabwidget.h \
    toolbutton.h \
    pushbutton.h \
    defs.h \
    mainmenu.h \
    database.h \
    framelesshelper.h \
    nodeitem.h \
    nettopoview.h \
    nettoposcene.h \
    portlinkitem.h

RESOURCES += \
    qtdirectui.qrc

FORMS += \
    tabwidget.ui
