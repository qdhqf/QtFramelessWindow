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
    treemode/treeitem.cpp \
    treemode/treemodel.cpp

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
    treemode/treeitem.h \
    treemode/treemodel.h

INCLUDEPATH +=  $$PWD/netplan \
                $$PWD/netres \
                $$PWD/locationview \
                $$PWD/netview \
                $$PWD/database \
                $$PWD/treemode \

RESOURCES += \
    qtdirectui.qrc

FORMS += \
    tabwidget.ui

DISTFILES += \
    image/Find/find.png \
    image/new/loading.gif \
    image/new/flags/flag_arab.png \
    image/new/flags/flag_brazil.png \
    image/new/flags/flag_bulgaria.png \
    image/new/flags/flag_china.png \
    image/new/flags/flag_czech.png \
    image/new/flags/flag_finland.png \
    image/new/flags/flag_france.png \
    image/new/flags/flag_galicia.png \
    image/new/flags/flag_germany.png \
    image/new/flags/flag_great_britain.png \
    image/new/flags/flag_greece.png \
    image/new/flags/flag_hungary.png \
    image/new/flags/flag_india.png \
    image/new/flags/flag_iran.png \
    image/new/flags/flag_italy.png \
    image/new/flags/flag_japan.png \
    image/new/flags/flag_lithuania.png \
    image/new/flags/flag_netherlands.png \
    image/new/flags/flag_poland.png \
    image/new/flags/flag_portugal.png \
    image/new/flags/flag_romania.png \
    image/new/flags/flag_russia.png \
    image/new/flags/flag_serbian.png \
    image/new/flags/flag_slovakia.png \
    image/new/flags/flag_south_korea.png \
    image/new/flags/flag_spain.png \
    image/new/flags/flag_sweden.png \
    image/new/flags/flag_taiwan.png \
    image/new/flags/flag_tajikistan.png \
    image/new/flags/flag_turkey.png \
    image/new/flags/flag_ukraine.png \
    image/new/flags/flag_vietnam.png \
    image/new/share/evernote.png \
    image/new/share/facebook.png \
    image/new/share/gplus.png \
    image/new/share/linkedin.png \
    image/new/share/livejournal.png \
    image/new/share/pocket.png \
    image/new/share/printfriendly.png \
    image/new/share/twitter.png \
    image/new/share/vk.png \
    image/new/adblock-disabled.png \
    image/new/adblock.png \
    image/new/adblock_big.png \
    image/new/add-ico2.png \
    image/new/add.png \
    image/new/add_t.png \
    image/new/arrow_down.png \
    image/new/arrow_left.png \
    image/new/arrow_right.png \
    image/new/arrow_turn_left.png \
    image/new/arrow_up.png \
    image/new/back_page.png \
    image/new/backup.png \
    image/new/bullet_error.png \
    image/new/bullet_toggle_minus.png \
    image/new/bullet_toggle_plus.png \
    image/new/bullet_update.png \
    image/new/bulletNew.png \
    image/new/bulletRead.png \
    image/new/bulletUnread.png \
    image/new/cleanup.png \
    image/new/close.png \
    image/new/close_hover.png \
    image/new/column.png \
    image/new/control_play.png \
    image/new/delete.png \
    image/new/delete_t.png \
    image/new/download.png \
    image/new/editClear.png \
    image/new/email.png \
    image/new/exportFeeds.png \
    image/new/feedDefault.png \
    image/new/fi1.png \
    image/new/fi2.png \
    image/new/filter.png \
    image/new/filterOff.png \
    image/new/find.png \
    image/new/find_in_browser_s.png \
    image/new/find_in_news.png \
    image/new/find_in_news_s.png \
    image/new/findFeed.png \
    image/new/flash.png \
    image/new/flashstart.png \
    image/new/folder.png \
    image/new/folder_add.png \
    image/new/folder_delete.png \
    image/new/folder_star.png \
    image/new/folder_unread.png \
    image/new/forward_page.png \
    image/new/fullScreen.png \
    image/new/house.png \
    image/new/ico8-1.png \
    image/new/imagesOff.png \
    image/new/imagesOn.png \
    image/new/ImportFeeds.png \
    image/new/label_gray.png \
    image/new/label_green.png \
    image/new/label_orange.png \
    image/new/label_purple.png \
    image/new/label_red.png \
    image/new/label_yellow.png \
    image/new/layout_classic.png \
    image/new/layout_newspaper.png \
    image/new/list_clear.png \
    image/new/logo.png \
    image/new/logo_text.png \
    image/new/markRead.png \
    image/new/markReadAll.png \
    image/new/menu.png \
    image/new/news_i.png \
    image/new/noicon.png \
    image/new/options.png \
    image/new/page_copy.png \
    image/new/panel_hide.png \
    image/new/panel_show.png \
    image/new/preferencesFeed.png \
    image/new/printer.png \
    image/new/QuiteRSS16_NewNews.png \
    image/new/QuiteRSS16_NewNews1.png \
    image/new/quiterss_count.png \
    image/new/readSection.png \
    image/new/save_as.png \
    image/new/share.png \
    image/new/sortIndicatorA.png \
    image/new/sortIndicatorD.png \
    image/new/splashScreen.png \
    image/new/starOff.png \
    image/new/starOn.png \
    image/new/starSection.png \
    image/new/tab_go.png \
    image/new/trash.png \
    image/new/trayNews.png \
    image/new/triangleL.png \
    image/new/triangleR.png \
    image/new/triangleT.png \
    image/new/update_page.png \
    image/new/updateAllFeeds.png \
    image/new/updateFeed.png \
    image/new/warning.png \
    image/new/world.png \
    image/new/world_go.png \
    image/new/zoom.png \
    image/new/zoom_in.png \
    image/new/zoom_out.png \
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
