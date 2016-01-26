#include "titlebar.h"
#include "mainwindow.h"

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_bLeftButtonPress = false;
    CreateWidget();
    CreateLayout();
    CreateEventFiter();
    SetWidgetStyle();
}

TitleBar::~TitleBar()
{
}

//创建子部件
void TitleBar::CreateWidget()
{
    //图像标签--logo
    m_pLabelIcon = new QLabel(this);
    QPixmap objPixmap(":/image/logo.png");
    m_pLabelIcon->setPixmap(objPixmap.scaled(77,30));
    QSize iconSize = QSize(30,30);
    m_pBtnMenu = new QToolButton(this);
    QPixmap menupix(":/image/title_bar_menu.png");
    m_pBtnMenu->setIcon(menupix);
    m_pBtnMenu->setIconSize(iconSize);

    //按钮--最小化
    m_pBtnMin = new QToolButton(this);
    QPixmap minpix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    m_pBtnMin->setIcon(minpix);
    m_pBtnMin->setIconSize(iconSize);
    //SetBtnIcon(m_pBtnMin,eBtnStateDefault,true);
    //按钮--最大化/还原
    m_pBtnMax = new QToolButton(this);
    QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
    m_pBtnMax->setIcon(maxPix);
    m_pBtnMax->setIconSize(iconSize);
    //SetBtnIcon(m_pBtnMax,eBtnStateDefault,true);
    //按钮--关闭
    m_pBtnClose = new QToolButton(this);
    QPixmap closepix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    m_pBtnClose->setIcon(closepix);
    m_pBtnClose->setIconSize(iconSize);
    //获得子部件
    const QObjectList &objList = children();
    for(int nIndex=0; nIndex<objList.count();++nIndex)
    {
        //设置子部件的MouseTracking属性
        ((QWidget*)(objList.at(nIndex)))->setMouseTracking(true);
        //如果是QToolButton部件
        if(0==qstrcmp(objList.at(nIndex)->metaObject()->className(),"QToolButton"))
        {
            //连接pressed信号为slot_btnpress
            connect(((QToolButton*)(objList.at(nIndex))),SIGNAL(pressed()),this,SLOT(slot_btnpress()));
            //连接clicked信号为slot_btnclick
            connect(((QToolButton*)(objList.at(nIndex))),SIGNAL(clicked()),this,SLOT(slot_btnclick()));
            //设置顶部间距
            ((QToolButton*)(objList.at(nIndex)))->setContentsMargins(0,VALUE_DIS,0,0);
        }
    }
}

//设置子部件样式(qss)
void TitleBar::SetWidgetStyle()
{
    //设置标签的文本颜色，大小等以及按钮的边框
    setStyleSheet("QLabel{color:#CCCCCC;font-size:12px;font-weight:bold;}QToolButton{border:0px;}");
    //设置左边距
    //m_pLabelTitle->setStyleSheet("margin-left:6px;");
    //设置右边距以及鼠标移上去时的文本颜色
   // m_pLabelVersion->setStyleSheet("QLabel{margin-right:10px;}QLabel:hover{color:#00AA00;}");
}

//创建设置布局
void TitleBar::CreateLayout()
{
    //水平布局
    m_pLayout = new QHBoxLayout(this);
    //添加部件
    m_pLayout->addWidget(m_pLabelIcon);

    m_pLayout->addWidget(m_pBtnMenu);
    m_pLayout->addWidget(m_pBtnMin);
    m_pLayout->addWidget(m_pBtnMax);
    m_pLayout->addWidget(m_pBtnClose);
    //设置Margin
    m_pLayout->setContentsMargins(0,0,/*VALUE_DIS*/0,0);
    //设置部件之间的space
    m_pLayout->setSpacing(0);
    setLayout(m_pLayout);
}

//设置按钮不同状态下的图标
void TitleBar::SetBtnIcon(QToolButton *pBtn,eBtnMoustState state,bool bInit/*=false*/)
{
    //获得图片路径
    QString strImagePath = GetBtnImagePath(pBtn,bInit);
    //创建QPixmap对象
    QPixmap objPixmap(strImagePath);
    //得到图像宽和高
    int nPixWidth = objPixmap.width();
    int nPixHeight = objPixmap.height();
    //如果状态不是无效值
    if(state!=eBtnStateNone)
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
const QString TitleBar::GetBtnImagePath(QToolButton *pBtn,bool bInit/*=false*/)
{
    QString strImagePath;

    if(m_pBtnMenu==pBtn)
    {
        strImagePath = ":/image/title_bar_menu.png";
    }
    //最小化
    if(m_pBtnMin==pBtn)
    {
        strImagePath = ":/image/sys_button_min.png";
    }
    //最大化/还原按钮，所以包括最大化和还原两张图片
    if(m_pBtnMax==pBtn)
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
    if(m_pBtnClose==pBtn)
    {
        strImagePath = ":/image/sys_button_close.png";
    }
    return strImagePath;
}


//创建事件过滤器
void TitleBar::CreateEventFiter()
{
    m_pBtnMenu->installEventFilter(this);
    m_pBtnMin->installEventFilter(this);
    m_pBtnMax->installEventFilter(this);
    m_pBtnClose->installEventFilter(this);
}

//事件过滤
bool TitleBar::eventFilter(QObject *obj, QEvent *event)
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
    if(m_pBtnMenu==obj)
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
void TitleBar::slot_btnpress()
{
 /*   QToolButton *pBtn = (QToolButton*)(sender());
    if(pBtn==m_pBtnMin)
    {
        emit signal_min();
    }
    if(pBtn==m_pBtnMax)
    {
        emit signal_maxrestore();
    }
    if(pBtn==m_pBtnClose)
    {
        emit signal_close();
    }*/
}


//槽函数--slot_btnclick
void TitleBar::slot_btnclick()
{
    QToolButton *pBtn = (QToolButton*)(sender());
    if(pBtn==m_pBtnMin)
    {
        emit signal_min();
    }
    if(pBtn==m_pBtnMax)
    {
        emit signal_maxrestore();
    }
    if(pBtn==m_pBtnClose)
    {
        emit signal_close();
    }
}

/*
//鼠标按下事件
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
     if(event->y()<VALUE_DIS||event->x()<VALUE_DIS||rect().width()-event->x()<5)
        {
            event->ignore();
            return;
        }
        m_ptPress = event->globalPos();
        m_bLeftButtonPress = true;
    }
    event->ignore();
}
//鼠标移动事件
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bLeftButtonPress)
    {
        m_ptMove = event->globalPos();
        //移动主窗口
        //MainWindow *pMainWindow = (qobject_cast<MainWindow *>(parent()));
        //pMainWindow->move(pMainWindow->pos()+m_ptMove-m_ptPress);
        //重新设置m_ptPress;
        m_ptPress = m_ptMove;
    }
    event->ignore();
}
//鼠标释放事件
void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPress = false;
    }
     event->ignore();
}
*/
