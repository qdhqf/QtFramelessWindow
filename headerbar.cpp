

#include "headerbar.h"
#include "defs.h"


HeaderBar::HeaderBar(QWidget *parent) :
    QWidget(parent)
{
    setFixedHeight(HEADER_H);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    thisParent = parent;
    CreateWidget();
    CreateLayout();
    SetWidgetStyle();
}

HeaderBar::~HeaderBar()
{
}

void HeaderBar::updateMaxIcon(bool max)
{
    if(max)
    {
        if(NULL != ptrBtnMax) ptrBtnMax->setPix(":/image/sysButton/Restores.png");
    }
    else
    {
        if(NULL != ptrBtnMax) ptrBtnMax->setPix(":/image/sysButton/Maxs.png");
    }
}

void HeaderBar::CreateWidget() //创建子部件
{
    ptrLabelIcon = new QLabel(this);  //图像标签--logo
    QPixmap objPixmap(":/image/logo.png");
    ptrLabelIcon->setPixmap(objPixmap);
    tabBar = new TabBar(this);
    tabBar->addTab(QStringLiteral("拓扑"));

    tabBar->addTab(QStringLiteral("路径"));
/*
    tabBar->addTab(QStringLiteral("业务/电路"));
    tabBar->addTab(QStringLiteral("系统管理"));
    tabBar->addTab(QStringLiteral("没想好1"));
    tabBar->addTab(QStringLiteral("没想好2"));*/
    tabBar->setObjectName("tabBar");
    tabBar->setTabIcon(0,QIcon(":/image/toolButton/topo.png"));
    tabBar->setTabIcon(1,QIcon(":/image/toolButton/cable.png"));
    tabBar->setStyleSheet(QString("#tabBar QToolButton {border: 1px solid %1; border-radius: 2px; background: %2;}").
                  arg(qApp->palette().color(QPalette::Dark).name()).
                  arg(qApp->palette().background().color().name()));
    ptrBtnMenu = new PushButton(this);
    ptrBtnMenu->setPix(":/image/sysButton/Menus.png");

    ptrBtnMin = new PushButton(this);
    ptrBtnMin->setPix(":/image/sysButton/Mins.png");

    ptrBtnMax = new PushButton(this);
    ptrBtnMax->setPix(":/image/sysButton/Maxs.png");

    ptrBtnClose = new PushButton(this);
    ptrBtnClose->setPix(":/image/sysButton/Closes.png");

    connect(tabBar,SIGNAL(tabBarClicked(int)), this, SLOT(slot_sigTabClicked(int)));

    connect(ptrBtnMenu,SIGNAL(clicked()),this,SLOT(slot_menu()));
    connect(ptrBtnMax,SIGNAL(clicked()),this,SIGNAL(signal_maxrestore()));

    connect(ptrBtnMin,SIGNAL(clicked()),thisParent,SLOT(showMinimized()));
    connect(ptrBtnClose,SIGNAL(clicked()),thisParent,SLOT(close()));
}


void HeaderBar::SetWidgetStyle()  //设置子部件样式(qss)
{   
    //setStyleSheet("QWidget { border: none; padding: 0px; }");
    setAutoFillBackground(true);
    QPalette pal;
    QPixmap pix(":/image/head.png");
    pal.setBrush(backgroundRole(),QBrush(pix));
    setPalette(pal);

}


void HeaderBar::CreateLayout()  //创建设置布局
{ 
    ptrTitleLayout = new QHBoxLayout(); //水平布局
    ptrTitleLayout->setContentsMargins(2,2,2,0); //设置Margin
    ptrTitleLayout->setSpacing(0); //设置部件之间的space

    ptrTitleLayout->addWidget(ptrLabelIcon, 0, Qt::AlignCenter);  //添加部件
    ptrTitleLayout->addSpacing(20);
    ptrTitleLayout->addWidget(tabBar, 0, Qt::AlignBottom);
    ptrTitleLayout->addStretch();
    ptrTitleLayout->addWidget(ptrBtnMenu, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnMin, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnMax, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnClose, 0, Qt::AlignTop);
    setLayout(ptrTitleLayout);
}

void HeaderBar::slot_menu()
{
    QPoint pt = QCursor::pos();
    emit signal_menu(pt);
}

void HeaderBar::slot_sigTabClicked(int index)
{
   emit sigTabClicked(index);
}
