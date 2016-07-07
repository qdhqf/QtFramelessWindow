

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
    //CreateEventFiter();
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
    tabBar_ = new TabBar();
    tabBar_->addTab(QStringLiteral("拓扑"));
    tabBar_->addTab(QStringLiteral("路径"));
    tabBar_->setMinimumHeight(HEADER_H-4);
    tabBar_->setTabsClosable(true);

    ptrBtnMenu = new PushButton(this);
    ptrBtnMenu->setPix(":/image/sysButton/Menus.png");

    ptrBtnMin = new PushButton(this);
    ptrBtnMin->setPix(":/image/sysButton/Mins.png");

    ptrBtnMax = new PushButton(this);
    ptrBtnMax->setPix(":/image/sysButton/Maxs.png");

    ptrBtnClose = new PushButton(this);
    ptrBtnClose->setPix(":/image/sysButton/Closes.png");

    ///////Tool Button///////////////
  /*  ptrBtnSite = new ToolButton(":/image/toolButton/build.png",this);
    ptrBtnSite->setText("Building");
    ptrBtnDevice = new ToolButton(":/image/toolButton/wdm.png",this);
    ptrBtnDevice->setText("Devices");
    ptrBtnCable = new ToolButton(":/image/toolButton/cable.png",this);
    ptrBtnCable->setText("Connect");*/

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
    ptrTitleLayout->addWidget(ptrLabelIcon, 0, Qt::AlignCenter);  //添加部件
    ptrTitleLayout->addWidget(tabBar_, 0, Qt::AlignBottom);
    ptrTitleLayout->addStretch();
    ptrTitleLayout->addWidget(ptrBtnMenu, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnMin, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnMax, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnClose, 0, Qt::AlignTop);
    ptrTitleLayout->setContentsMargins(2,2,2,0); //设置Margin
    ptrTitleLayout->setSpacing(0); //设置部件之间的space

/*
    ptrToolLayout = new QHBoxLayout();
    ptrToolLayout->addWidget(ptrBtnSite,0,Qt::AlignTop);
    ptrToolLayout->addWidget(ptrBtnDevice,0,Qt::AlignTop);
    ptrToolLayout->addWidget(ptrBtnCable,0,Qt::AlignTop);

    ptrToolLayout->addStretch();
    ptrToolLayout->setContentsMargins(0,0,0,0); //设置Margin
    ptrToolLayout->setSpacing(0);
    ptrHeaderLayout =new QVBoxLayout(this);

    ptrHeaderLayout->addLayout(ptrTitleLayout);\
    ptrHeaderLayout->addLayout(ptrToolLayout);
    ptrHeaderLayout->setContentsMargins(2,2,2,2);
    ptrHeaderLayout->setSpacing(0);
    setLayout(ptrHeaderLayout);*/
    setLayout(ptrTitleLayout);
}

void HeaderBar::slot_menu()
{
    QPoint pt = QCursor::pos();
    emit signal_menu(pt);
}
