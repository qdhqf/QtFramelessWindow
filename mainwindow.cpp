
#include "mainwindow.h"
#include "headerbar.h"
#include "statusbar.h"
#include "defs.h"
#include "tabwidget.h"
#include "mainmenu.h"
#include "framelesshelper.h"


//#include "myitem.h"
#include "nodeitem.h"
#include "nettopoview.h"
#include "nettoposcene.h"
#include "portlinkitem.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
  //setWindowFlags(Qt::CustomizeWindowHint);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);

    ptrHeaderBar = new HeaderBar(this);//创建标题栏
    ptrStatusBar = new StatusBar(this);//创建状态栏
    QString msg = "Ready";
    ptrStatusBar->setMessage(msg);

    ptrMainLayout = new QVBoxLayout(this);//创建布局
    ptrMainLayout->addWidget(ptrHeaderBar);//将部件加入到布局中
    QSplitter *mainSplitter = new QSplitter(this);
    TabWidget *t1 = new TabWidget(this);

    NetTopoScene *scene = new NetTopoScene();
    scene->setSceneRect(-200, -150, 400, 300);


    NodeItem *item1 = new NodeItem();

   /* QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/image/NodeIcon/OTN.png"));
    item->setFlags(QGraphicsItem::ItemIsFocusable);
    item->setFlags(QGraphicsItem::ItemIsMovable);*/
    item1->setPos( - 90, -50);
    scene->addItem(item1);
    NodeItem *item2 = new NodeItem();
    item2->setPos( 90, -50);
    scene->addItem(item2);

    NodeItem *item3 = new NodeItem();
    item3->setPos( 0, 100);
    scene->addItem(item3);


    PortLinkItem *link1 = new PortLinkItem(item1,item2);
    scene->addItem(link1);

    PortLinkItem *link2 = new PortLinkItem(item1,item3);
    scene->addItem(link2);

    PortLinkItem *link3 = new PortLinkItem(item2,item3);
    scene->addItem(link3);
    //scene->clearSelection();
    NetTopoView *v =new NetTopoView(this);
    v->setScene(scene);
    v->setBackgroundBrush(QPixmap(":image/background.png"));
    //view.show();

    //QGraphicsView *v = new QGraphicsView(this);
    mainSplitter->addWidget(t1);
    mainSplitter->addWidget(v);
    mainSplitter->setStretchFactor(0,20);
    mainSplitter->setStretchFactor(1,80);
    mainSplitter->setAutoFillBackground(true);
    ptrMainLayout->addWidget(mainSplitter);
    ptrMainLayout->addWidget(ptrStatusBar);
    //设置间距与边缘空白
    ptrMainLayout->setSpacing(0);
    ptrMainLayout->setContentsMargins(VALUE_DIS,VALUE_DIS,VALUE_DIS,VALUE_DIS);

    setMinimumWidth(800);
    setMinimumHeight(600);


    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setBorderWidth(VALUE_DIS);
    pHelper->setTitleHeight(HEADER_H);  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放

    connect(ptrHeaderBar, SIGNAL(signal_menu(QPoint)), this, SLOT(showMenu(QPoint)));
    connect(ptrHeaderBar, SIGNAL(signal_maxrestore()), this, SLOT(showMaxRestore()));
    db.initdbcon();
}

MainWindow::~MainWindow()
{

}

void MainWindow::showMenu(QPoint pt)
{
   MainMenu *m = new MainMenu(this);
   m->exec(pt);
}

void MainWindow::showMaxRestore()
{
    if(isMaximized()||isFullScreen())
    {
        this->showNormal();
    }
    else
    {
        this->showMaximized();
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::WindowStateChange)
    {
        if(isMaximized()||isFullScreen())
        {
            ptrHeaderBar->updateMaxIcon();
        }
        else
        {
            ptrHeaderBar->updateMaxIcon(false);
        }
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QBitmap objBitmap(size());//生成一张位图
    QPainter painter(&objBitmap); //QPainter用于在位图上绘画
    painter.fillRect(rect(),Qt::white);//填充位图矩形框(用白色填充)
    painter.setBrush(QColor(0,0,0));
    painter.drawRoundedRect(this->rect(),10,10); //在位图上画圆角矩形(用黑色填充)
    setMask(objBitmap); //使用setmask过滤即可
    QFrame::paintEvent(event);
}


