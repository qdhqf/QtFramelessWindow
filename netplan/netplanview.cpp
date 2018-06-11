#include "netplanview.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "nodeitem.h"
#include "portlinkitem.h"

NetPlanView::NetPlanView(QWidget *parent) : QWidget(parent)
{
    planToolBar = new QToolBar(this);
    planToolBar->setObjectName("planToolBar");
    planToolBar->setStyleSheet(QString("#planToolBar { border-bottom: 1px solid %1;}").
                               arg(qApp->palette().color(QPalette::Dark).name()));
    fillToolBar();

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(-683, -384, 1366, 768);

    QGraphicsPixmapItem *pixItem =new QGraphicsPixmapItem();
    pixItem->setPixmap(QPixmap(":image/background.png"));
    pixItem->setOpacity(0.3);
    pixItem->setPos(-517,-379);
    pixItem->setZValue(-500.0);
    scene->addItem(pixItem);


    NodeItem *item1 = new NodeItem();
   // item1->setPlainText(QStringLiteral("ITMC(中蒙)-N-二连浩特廉租楼-H-OTM/6853-ITMC(中蒙)-N-二连浩特廉租楼-H-OTM-01"));
    item1->setPos( - 90, -50);
    scene->addItem(item1);
    NodeItem *item2 = new NodeItem();
    //item2->setPlainText(QStringLiteral("ITMC(中蒙)-N-二连浩特廉租楼-H-OTM/6853-ITMC(中蒙)-N-二连浩特廉租楼-H-OTM-02"));
    item2->setPos( 90, -50);
    scene->addItem(item2);

    NodeItem *item3 = new NodeItem();
    //item3->setPlainText(QStringLiteral("ITMC(中蒙)-N-二连浩特廉租楼-H-OTM/6853-ITMC(中蒙)-N-二连浩特廉租楼-H-OTM-03"));
    item3->setPos( 0, 100);
    scene->addItem(item3);


    PortLinkItem *link1 = new PortLinkItem(item1,item2);
    scene->addItem(link1);

    PortLinkItem *link2 = new PortLinkItem(item1,item3);
    scene->addItem(link2);

    PortLinkItem *link3 = new PortLinkItem(item2,item3);
    scene->addItem(link3);

    QGraphicsView *v =new QGraphicsView(this);

    v->setScene(scene);
    v->setFrameStyle(QFrame::NoFrame);

    QVBoxLayout *planLay = new QVBoxLayout(this);
    planLay->setMargin(0);
    planLay->setSpacing(0);
    planLay->addWidget(planToolBar);
    planLay->addWidget(v);;
    setLayout(planLay);

}


void NetPlanView::fillToolBar()
{
    QAction *actAdd = new QAction(this);
    actAdd->setText("Add");
    actAdd->setIcon(QIcon(":/image/naviBar/add.png"));
    planToolBar->addAction(actAdd);
    planToolBar->addSeparator();

    QAction *actFil = new QAction(this);
    actFil->setText("Filter");
    actFil->setIcon(QIcon(":/image/naviBar/filter.png"));
    planToolBar->addAction(actFil);
    planToolBar->addSeparator();
}
