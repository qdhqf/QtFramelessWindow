#include "headerbar.h"
#include "mainwindow.h"

HeaderBar::HeaderBar(QWidget *parent) :
    QWidget(parent)
{
    setFixedHeight(HEADER_H);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    CreateWidget();
    CreateLayout();
    CreateEventFiter();
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

    QSize iconSize = QSize(30,30);

    ptrBtnMenu = new QToolButton(this);
    QPixmap menupix(":/image/title_bar_menu.png");
    ptrBtnMenu->setIcon(menupix);
    ptrBtnMenu->setIconSize(iconSize);

    ptrBtnMin = new QToolButton(this); //按钮--最小化
    QPixmap minpix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    ptrBtnMin->setIcon(minpix);
    ptrBtnMin->setIconSize(iconSize);

    ptrBtnMax = new QToolButton(this); //按钮--最大化/还原
    QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
    ptrBtnMax->setIcon(maxPix);
    ptrBtnMax->setIconSize(iconSize);

    ptrBtnClose = new QToolButton(this);  //按钮--关闭
    QPixmap closepix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    ptrBtnClose->setIcon(closepix);
    ptrBtnClose->setIconSize(iconSize);

    const QObjectList &objList = children();   //获得子部件
    for(int nIndex=0; nIndex<objList.count();++nIndex)
    {
        ((QWidget*)(objList.at(nIndex)))->setMouseTracking(true);  //设置子部件的MouseTracking属性
        if(0==qstrcmp(objList.at(nIndex)->metaObject()->className(),"QToolButton"))  //如果是QToolButton部件
        {
            connect(((QToolButton*)(objList.at(nIndex))),SIGNAL(pressed()),this,SLOT(slot_btnpress()));  //连接pressed信号为slot_btnpress
            connect(((QToolButton*)(objList.at(nIndex))),SIGNAL(clicked()),this,SLOT(slot_btnclick())); //连接clicked信号为slot_btnclick
            //((QToolButton*)(objList.at(nIndex)))->setContentsMargins(0,0,0,0);//设置顶部间距
        }
    }
}


void HeaderBar::SetWidgetStyle()  //设置子部件样式(qss)
{   
    setStyleSheet("QWidget {background-image:url(:/image/header.png);border:0px solid black;}");
    //setStyleSheet("QLabel{color:#CCCCCC;font-size:12px;font-weight:bold;}QToolButton{border:0px;}"); //设置标签的文本颜色，大小等以及按钮的边框
    //设置左边距
    //m_pLabelTitle->setStyleSheet("margin-left:6px;");
    //设置右边距以及鼠标移上去时的文本颜色
   // m_pLabelVersion->setStyleSheet("QLabel{margin-right:10px;}QLabel:hover{color:#00AA00;}");
    setAutoFillBackground(true);
    QPalette pal;
    QPixmap pix(":/image/header.png");
    pal.setBrush(backgroundRole(),QBrush(pix));
    setPalette(pal);
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


void HeaderBar::SetBtnIcon(QToolButton *pBtn,eBtnMoustState state,bool bInit/*=false*/)  //设置按钮不同状态下的图标
{
    QString strImagePath = GetBtnImagePath(pBtn,bInit); //获得图片路径
    QPixmap objPixmap(strImagePath);  //创建QPixmap对象

    int nPixWidth = objPixmap.width(); //得到图像宽和高
    int nPixHeight = objPixmap.height();

    if(state!=eBtnStateNone)//如果状态不是无效值
    {
        /*设置按钮图片
        按钮的图片是连续在一起的，如前1/4部分表示默认状态下的图片部分,接后的1/4部分表示鼠标移到按钮状态下的图片部分
        */
        pBtn->setIcon(objPixmap.copy((nPixWidth/4)*(state-1),0,nPixWidth/4,nPixHeight));
        //设置按钮图片大小
        pBtn->setIconSize(QSize(nPixWidth/4,nPixHeight));
    }
}


//获得图片路径(固定值)
const QString HeaderBar::GetBtnImagePath(QToolButton *pBtn,bool bInit/*=false*/)
{
    QString strImagePath;

    if(ptrBtnMenu==pBtn)
    {
        strImagePath = ":/image/title_bar_menu.png";
    }
    //最小化
    if(ptrBtnMin==pBtn)
    {
        strImagePath = ":/image/sys_button_min.png";
    }
    //最大化/还原按钮，所以包括最大化和还原两张图片
    if(ptrBtnMax==pBtn)
    {
        //如果是初始设置或者主界面的最大化标志不为真(其中MainWindow::Instance()使用单例设计模式)
        if(bInit==true /*|| MainWindow::Instance()->GetMaxWin()==false*/)
        {
            //最大化按钮图片路径
            strImagePath = ":/image/sys_button_max.png";
        }
        else
        {
            //还原按钮图片路径
            strImagePath = ":/image/sys_button_restore.png";
        }
    }
    //关闭按钮
    if(ptrBtnClose==pBtn)
    {
        strImagePath = ":/image/sys_button_close.png";
    }
    return strImagePath;
}



void HeaderBar::CreateEventFiter()//创建事件过滤器
{
    ptrBtnMenu->installEventFilter(this);
    ptrBtnMin->installEventFilter(this);
    ptrBtnMax->installEventFilter(this);
    ptrBtnClose->installEventFilter(this);
}

//事件过滤
bool HeaderBar::eventFilter(QObject *obj, QEvent *event)
{
    //按钮状态
    eBtnMoustState eState = eBtnStateNone;
    //判断事件类型--QEvent::Enter
    if (event->type() == QEvent::Enter)
    {
        eState = eBtnStateHover;
    }
    //判断事件类型--QEvent::Leave
    if (event->type() == QEvent::Leave)
    {
        eState = eBtnStateDefault;
    }
    //判断事件类型--QEvent::MouseButtonPress
    if (event->type() == QEvent::MouseButtonPress && ((QMouseEvent*)(event))->button()== Qt::LeftButton)
    {
        eState = eBtnStatePress;
    }
    //判断目标
    if(ptrBtnMenu==obj)
    {
        //如果状态有效
        if(eState != eBtnStateNone)
        {
            //根据状态设置按钮图标
            //SetBtnIcon((QToolButton *)obj,eState);
            return false;
        }
    }
    return QWidget::eventFilter(obj,event);
}

//槽函数--slot_btnpress()
void HeaderBar::slot_btnpress()
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


//槽函数--slot_btnclick
void HeaderBar::slot_btnclick()
{
    QToolButton *ptrBtn = (QToolButton*)(sender());
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

