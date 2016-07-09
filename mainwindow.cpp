#include <QtWidgets>
#include "mainwindow.h"
#include "headerbar.h"
#include "statusbar.h"
#include "defs.h"
#include "mainmenu.h"
#include "framelesshelper.h"



#include "nodeitem.h"
#include "nettopoview.h"
#include "nettoposcene.h"
#include "portlinkitem.h"
#include "leftnavi.h"

#include <QTime>

MainWindow::MainWindow(QFrame *parent)
    : QFrame(parent),isLeftNaviVisuable(true)
{
    setWindowFlags(Qt::FramelessWindowHint);
  //setWindowFlags(Qt::CustomizeWindowHint);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);
    QString fileName("/style/system.qss");
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
      file.setFileName(":/style/system.qss");
      file.open(QFile::ReadOnly);
    }
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

 /*   QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);*/


    ptrHeaderBar = new HeaderBar(this);//创建标题栏

    ptrStatusBar = new StatusBar(this);//创建状态栏
    QString msg = "Ready";
    ptrStatusBar->setMessage(msg);





    lft = new LeftNavi(this);
    lft->setFrameStyle(QFrame::NoFrame);
    //lft->setStyleSheet("#LeftNavi { border: none; padding: 0px; }");


    QSplitter *mainSplitter = new QSplitter(this);
    mainSplitter->setFrameStyle(QFrame::NoFrame);
    mainSplitter->setHandleWidth(1);
    mainSplitter->setStyleSheet(
                QString("QSplitter::handle {background: qlineargradient("
                        "x1: 0, y1: 0, x2: 0, y2: 1,"
                        "stop: 0 %1, stop: 0.07 %2);}").
                arg(qApp->palette().background().color().name()).
                arg(qApp->palette().color(QPalette::Dark).name()));

    mainSplitter->setChildrenCollapsible(false);




    NetTopoScene *scene = new NetTopoScene();
    scene->setSceneRect(-683, -384, 1366, 768);

    QGraphicsPixmapItem *pixItem =new QGraphicsPixmapItem();
    pixItem->setPixmap(QPixmap(":image/background.png"));
    pixItem->setOpacity(0.3);
    pixItem->setPos(-517,-379);
    pixItem->setZValue(-500.0);
    scene->addItem(pixItem);


    NodeItem *item1 = new NodeItem();
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

    NetTopoView *v =new NetTopoView(this);



    v->setScene(scene);
    v->setFrameStyle(QFrame::NoFrame);
    createToolBarNull();
    mainSplitter->addWidget(lft);
    mainSplitter->addWidget(v);
    mainSplitter->setStretchFactor(20,80);

    QHBoxLayout *ptrMainLayout = new QHBoxLayout();
    ptrMainLayout->setMargin(0);
    ptrMainLayout->setSpacing(0);
    ptrMainLayout->addWidget(pushButtonNull_);
    ptrMainLayout->addWidget(mainSplitter);

    QVBoxLayout *ptrCentreLayout = new QVBoxLayout(this);//创建布局
    ptrCentreLayout->addWidget(ptrHeaderBar);//将部件加入到布局中
    //ptrCentreLayout->addWidget(mainSplitter);
    ptrCentreLayout->addLayout(ptrMainLayout);
    ptrCentreLayout->addWidget(ptrStatusBar);

    ptrCentreLayout->setSpacing(0);  //设置间距与边缘空白
    ptrCentreLayout->setContentsMargins(VALUE_DIS,VALUE_DIS,VALUE_DIS,VALUE_DIS);

    setMinimumWidth(800);
    setMinimumHeight(600);


     createActions();


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

void MainWindow::createToolBarNull()
{
    pushButtonNull_ = new QPushButton(this);
    pushButtonNull_->setObjectName("pushButtonNull");
    pushButtonNull_->setIcon(QIcon(":/image/triangleR.png"));
    pushButtonNull_->setFixedWidth(10);
    pushButtonNull_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pushButtonNull_->setFocusPolicy(Qt::NoFocus);
    pushButtonNull_->setStyleSheet("background: #E8E8E8; border: none; padding: 0px;");
}

void MainWindow::slotVisibledLeftWiew()
{
   if(isLeftNaviVisuable){
       pushButtonNull_->setIcon(QIcon(":/image/triangleL.png"));
       lft->hide();
   }
   else{
       pushButtonNull_->setIcon(QIcon(":/image/triangleR.png"));
       lft->show();
   }
   isLeftNaviVisuable = !isLeftNaviVisuable;
}

void MainWindow::createActions()
{
   connect(pushButtonNull_, SIGNAL(clicked()),  this, SLOT(slotVisibledLeftWiew()));
}
