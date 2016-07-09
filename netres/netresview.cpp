#include "NetResView.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "nodeitem.h"
#include "portlinkitem.h"

NetResView::NetResView(QWidget *parent) : QWidget(parent)
{
    resToolBar = new QToolBar(this);
    resToolBar->setObjectName("resToolBar");
    resToolBar->setStyleSheet(QString("#resToolBar { border-bottom: 1px solid %1;}").
                               arg(qApp->palette().color(QPalette::Dark).name()));
    fillToolBar();

    QTableWidget *table = new QTableWidget(this);
    table->setStyleSheet("QTableWidget { border: none; padding: 0px;}");
    table->setColumnCount(5);
    table->setRowCount(100);

   // table->setHorizontalHeaderLabels();
    QVBoxLayout *planLay = new QVBoxLayout(this);
    planLay->setMargin(0);
    planLay->setSpacing(0);
    planLay->addWidget(resToolBar);
    planLay->addWidget(table);;
    setLayout(planLay);

}


void NetResView::fillToolBar()
{
    QAction *actAdd = new QAction(this);
    actAdd->setText("Add");
    actAdd->setIcon(QIcon(":/image/naviBar/update.png"));
    resToolBar->addAction(actAdd);
    resToolBar->addSeparator();

    QAction *actFil = new QAction(this);
    actFil->setText("Filter");
    actFil->setIcon(QIcon(":/image/naviBar/find.png"));
    resToolBar->addAction(actFil);
    resToolBar->addSeparator();
}
