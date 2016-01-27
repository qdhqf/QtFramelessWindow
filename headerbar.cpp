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


void HeaderBar::CreateWidget() //创建子部件
{

    ptrLabelIcon = new QLabel(this);  //图像标签--logo
    QPixmap objPixmap(":/image/logo.png");
    ptrLabelIcon->setPixmap(objPixmap.scaled(77,30));

    ptrBtnMenu = new PushButton(this);
    ptrBtnMenu->setPix("menu.png");


    ptrBtnMin = new PushButton(this);
    ptrBtnMin->setPix("min.png");


    ptrBtnMax = new PushButton(this);
    ptrBtnMax->setPix("max.png");

    ptrBtnClose = new PushButton(this);
    ptrBtnClose->setPix("close.png");


    const QObjectList &objList = children();   //获得子部件
    for(int nIndex=0; nIndex<objList.count();++nIndex)
    {
        ((QWidget*)(objList.at(nIndex)))->setMouseTracking(true);  //设置子部件的MouseTracking属性
        if(0==qstrcmp(objList.at(nIndex)->metaObject()->className(),"PushButton"))  //如果是QToolButton部件
        {
            connect(((PushButton*)(objList.at(nIndex))),SIGNAL(pressed()),this,SLOT(slot_btnpress()));  //连接pressed信号为slot_btnpress
            connect(((PushButton*)(objList.at(nIndex))),SIGNAL(clicked()),this,SLOT(slot_btnclick())); //连接clicked信号为slot_btnclick
           ((QToolButton*)(objList.at(nIndex)))->setContentsMargins(0,0,0,0);//设置顶部间距
        }
    }
}


void HeaderBar::SetWidgetStyle()  //设置子部件样式(qss)
{   
    //setStyleSheet("QWidget {background-image:url(:/image/header.png);border:0px solid black;}");
    //setStyleSheet("QLabel{color:#CCCCCC;font-size:12px;font-weight:bold;}QToolButton{border:0px;}"); //设置标签的文本颜色，大小等以及按钮的边框
    //设置左边距
    //m_pLabelTitle->setStyleSheet("margin-left:6px;");
    //设置右边距以及鼠标移上去时的文本颜色
   // m_pLabelVersion->setStyleSheet("QLabel{margin-right:10px;}QLabel:hover{color:#00AA00;}");
   /* setAutoFillBackground(true);
    QPalette pal;
    QPixmap pix(":/image/header.png");
    pal.setBrush(backgroundRole(),QBrush(pix));
    setPalette(pal);*/
}


void HeaderBar::CreateLayout()  //创建设置布局
{ 
    ptrTitleLayout = new QHBoxLayout(this); //水平布局
    ptrTitleLayout->addWidget(ptrLabelIcon, 0, Qt::AlignTop);  //添加部件
    ptrTitleLayout->addStretch();
    ptrTitleLayout->addWidget(ptrBtnMenu, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnMin, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnMax, 0, Qt::AlignTop);
    ptrTitleLayout->addWidget(ptrBtnClose, 0, Qt::AlignTop);
    ptrTitleLayout->setContentsMargins(0,0,0,0); //设置Margin
    ptrTitleLayout->setSpacing(0);
     //设置部件之间的space

    ptrToolLayout = new QHBoxLayout(this);
   /* QWidget *widget = new QWidget(this);
    ptrToolLayout->addWidget(widget);*/
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

