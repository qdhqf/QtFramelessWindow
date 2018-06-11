#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T22:25:24
#
#-------------------------------------------------

QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TransLite
TEMPLATE = app

RC_ICONS = otn.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    headerbar.cpp \
    statusbar.cpp \
    pushbutton.cpp \
    toolbutton.cpp \
    mainmenu.cpp \
    framelesshelper.cpp \
    nodeitem.cpp \
    portlinkitem.cpp \
    tabbar.cpp \
    leftnavi.cpp \
    findtext.cpp \
    netplan/netplanview.cpp \
    netres/netresview.cpp \
    database/database.cpp \
    treeview/treeitem.cpp \
    treeview/treemodel.cpp

HEADERS  += mainwindow.h \
    statusbar.h \
    headerbar.h \
    toolbutton.h \
    pushbutton.h \
    defs.h \
    mainmenu.h \
    framelesshelper.h \
    nodeitem.h \
    portlinkitem.h \
    tabbar.h \
    leftnavi.h \
    findtext.h \
    netplan/netplanview.h \
    netres/netresview.h \
    database/database.h \
    treeview/treeitem.h \
    treeview/treemodel.h

INCLUDEPATH +=  $$PWD/netplan \
                $$PWD/netres \
                $$PWD/netview \
                $$PWD/database \
                $$PWD/treeview \

RESOURCES += \
    qtdirectui.qrc

FORMS += \
    tabwidget.ui

DISTFILES += \
    image/Find/find.png \
    image/NodeIcon/big/OLA.png \
    image/NodeIcon/big/OTN.png \
    image/NodeIcon/big/OTN2LEFT.png \
    image/NodeIcon/big/OTN2RIGHT.png \
    image/NodeIcon/big/ROUTER.png \
    image/NodeIcon/small/OLA.png \
    image/NodeIcon/small/OTN.png \
    image/NodeIcon/small/OTN2LEFT.png \
    image/NodeIcon/small/OTN2RIGHT.png \
    image/NodeIcon/small/ROUTER.png \
    OTN.ico \
    README.md
