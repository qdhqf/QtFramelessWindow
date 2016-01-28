#include "headerbar.h"
#include "mainwindow.h"


HeaderBar::HeaderBar(QWidget *parent) :
    QWidget(parent)
{
    setFixedHeight(HEADER_H);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

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
        if(NULL != ptrBtnMax) ptrBtnMax->setPix("restore.png");
    }
    else
    {
        if(NULL != ptrBtnMax) ptrBtnMax->setPix("max.png");
    }
}

void HeaderBar::CreateWidget() //创建子部件
{

    ptrLabelIcon = new QLabel();  //图像标签--logo
    QPixmap objPixmap(":/image/logo.png");
    ptrLabelIcon->setPixmap(objPixmap);

    ptrBtnMenu = new PushButton();
    ptrBtnMenu->setPix("menu.png");

    ptrBtnMin = new PushButton();
    ptrBtnMin->setPix("min.png");

    ptrBtnMax = new PushButton();
    ptrBtnMax->setPix("max.png");

    ptrBtnClose = new PushButton();
    ptrBtnClose->setPix("close.png");

    ///////Tool Button///////////////
    ptrBtnSite = new ToolButton(":/image/toolButton/build.png",this);
    ptrBtnSite->setText("Building");
    ptrBtnDevice = new ToolButton(":/image/toolButton/wdm.png",this);
    ptrBtnDevice->setText("Devices");
    ptrBtnCable = new ToolButton(":/image/toolButton/cable.png");
    ptrBtnCable->setText("Connect");

    connect(ptrBtnMenu,SIGNAL(clicked()),this,SLOT(slot_btnclick()));
    connect(ptrBtnMin,SIGNAL(clicked()),this,SLOT(slot_btnclick()));
    connect(ptrBtnMax,SIGNAL(clicked()),this,SLOT(slot_btnclick()));
    connect(ptrBtnClose,SIGNAL(clicked()),this,SLOT(slot_btnclick()));
}


void HeaderBar::SetWidgetStyle()  //设置子部件样式(qss)
{   
    setAutoFillBackground(true);
    QPalette pal;
    QPixmap pix(":/image/header.png");
    pal.setBrush(backgroundRole(),QBrush(pix));
    setPalette(pal);
}


void HeaderBar::CreateLayout()  //创建设置布局
{ 
    ptrTitleLayout = new QHBoxLayout(); //水平布局
    ptrTitleLayout->addWidget(ptrLabelIcon, 0, Qt::AlignTop);  //添加部件
    ptrTitleLayout->addStretch();
    ptrTitleLayout->addWidget(ptrBtnMenu, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnMin, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnMax, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnClose, 0, Qt::AlignTop);
    ptrTitleLayout->setContentsMargins(2,2,2,2); //设置Margin
    ptrTitleLayout->setSpacing(0); //设置部件之间的space


    ptrToolLayout = new QHBoxLayout();
    ptrToolLayout->addWidget(ptrBtnSite,0,Qt::AlignBottom);
    ptrToolLayout->addWidget(ptrBtnDevice,0,Qt::AlignBottom);
    ptrToolLayout->addWidget(ptrBtnCable,0,Qt::AlignBottom);

    ptrToolLayout->addStretch();
    ptrToolLayout->setContentsMargins(2,2,2,2); //设置Margin
    ptrToolLayout->setSpacing(0);
    ptrHeaderLayout =new QVBoxLayout(this);

    ptrHeaderLayout->addLayout(ptrTitleLayout);\
    ptrHeaderLayout->addLayout(ptrToolLayout);
    ptrHeaderLayout->setContentsMargins(0,0,0,0); //设置Margin
    ptrHeaderLayout->setSpacing(0);
    setLayout(ptrHeaderLayout);
}




void HeaderBar::slot_btnpress()   //槽函数--slot_btnpress()
{
 /*   QToolButton *pBtn = (QToolButton*)(sender());
    if(pBtn==ptrBtnMin)
    {
        emit signal_min();
    }
    if(pBtn==ptrBtnMax)
    {
        emit signal_maxrestore();
    }
    if(pBtn==ptrBtnClose)
    {
        emit signal_close();
    }*/
}



void HeaderBar::slot_btnclick()  //槽函数--slot_btnclick
{
    PushButton *ptrBtn = (PushButton*)(sender());
    if(ptrBtn==ptrBtnMin)
    {
        emit signal_min();
    }
    if(ptrBtn==ptrBtnMax)
    {
        emit signal_maxrestore();
    }
    if(ptrBtn==ptrBtnClose)
    {
        emit signal_close();
    }
}

