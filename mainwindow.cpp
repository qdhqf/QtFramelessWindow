#include "mainwindow.h"
#include "titlebar.h"
#include "toolbar.h"
#include "contentwidget.h"
#include "statusbar.h"


//////////////Begin CursorPosCalculator//////////////
int CursorPosCalculator::m_nBorderWidth = 5;
int CursorPosCalculator::m_nTitleHeight = 30;

/***** CursorPosCalculator *****/
CursorPosCalculator::CursorPosCalculator()
{
    reset();
}

void CursorPosCalculator::reset()
{
    m_bOnEdges = false;
    m_bOnLeftEdge = false;
    m_bOnRightEdge = false;
    m_bOnTopEdge = false;
    m_bOnBottomEdge = false;
    m_bOnTopLeftEdge = false;
    m_bOnBottomLeftEdge = false;
    m_bOnTopRightEdge  = false;
    m_bOnBottomRightEdge = false;
}

void CursorPosCalculator::recalculate(const QPoint &gMousePos, const QRect &frameRect)
{
    int globalMouseX = gMousePos.x();
    int globalMouseY = gMousePos.y();

    int frameX = frameRect.x();
    int frameY = frameRect.y();

    int frameWidth = frameRect.width();
    int frameHeight = frameRect.height();

    m_bOnLeftEdge = (globalMouseX >= frameX &&
                  globalMouseX <= frameX + m_nBorderWidth );


    m_bOnRightEdge = (globalMouseX >= frameX + frameWidth - m_nBorderWidth &&
                   globalMouseX <= frameX + frameWidth);

    m_bOnTopEdge = (globalMouseY >= frameY &&
                 globalMouseY <= frameY + m_nBorderWidth );

    m_bOnBottomEdge = (globalMouseY >= frameY + frameHeight - m_nBorderWidth &&
                    globalMouseY <= frameY + frameHeight);

    m_bOnTopLeftEdge = m_bOnTopEdge && m_bOnLeftEdge;
    m_bOnBottomLeftEdge = m_bOnBottomEdge && m_bOnLeftEdge;
    m_bOnTopRightEdge = m_bOnTopEdge && m_bOnRightEdge;
    m_bOnBottomRightEdge = m_bOnBottomEdge && m_bOnRightEdge;

    m_bOnEdges = m_bOnLeftEdge || m_bOnRightEdge || m_bOnTopEdge || m_bOnBottomEdge;
}
//////////////End CursorPosCalculator//////////////


MainWindow::MainWindow(QWidget *parent)
    : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
  //setWindowFlags(Qt::CustomizeWindowHint);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);

    ptrTitleBar = new TitleBar();//创建标题栏
    ptrTitleBar->setStyleSheet("QWidget {border:1px solid black;}");
    ptrToolBar = new ToolBar();//创建工具栏
    ptrToolBar->setStyleSheet("QWidget {border:1px solid black;}");
    ptrContentWidget = new ContentWidget();//创建内容区域
    ptrContentWidget->setStyleSheet("QWidget {border:1px solid black;}");
    ptrStatuBar = new StatuBar();//创建状态栏
    ptrStatuBar->setStyleSheet("QWidget {border:1px solid black;}");
    setStyleSheet("QFrame {background-image:url(:/image/frame.jpg);border:0px solid black;}");

    ptrMainLayout = new QVBoxLayout(this);//创建布局
    //将部件加入到布局中
    ptrMainLayout->addWidget(ptrTitleBar);
    ptrMainLayout->addWidget(ptrToolBar);
    ptrMainLayout->addWidget(ptrContentWidget);
    ptrMainLayout->addWidget(ptrStatuBar);
    //设置间距与边缘空白
    ptrMainLayout->setSpacing(1);
    ptrMainLayout->setContentsMargins(5,5,5,5);

    setMinimumWidth(400);
    setMinimumHeight(300);

    isLeftButtonPressed = false;
    isSizedCursor = false;
    isAllowAnyDrag = false;
    installEventFilter(this);
    connect(ptrTitleBar, SIGNAL(signal_min()), this, SLOT(showMinimized()));
    connect(ptrTitleBar, SIGNAL(signal_maxrestore()), this, SLOT(showMaxRestore()));
    connect(ptrTitleBar, SIGNAL(signal_close()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    setMouseTracking(false);
    setAttribute(Qt::WA_Hover, false);

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

void MainWindow::paintEvent(QPaintEvent *event)
{
 //生成一张位图
    QBitmap objBitmap(size());
    //QPainter用于在位图上绘画
    QPainter painter(&objBitmap);
    //填充位图矩形框(用白色填充)
    painter.fillRect(rect(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    //在位图上画圆角矩形(用黑色填充)
    painter.drawRoundedRect(this->rect(),10,10);
    //使用setmask过滤即可
    setMask(objBitmap);
    QFrame::paintEvent(event);
}

//鼠标双击事件
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y()<= ptrTitleBar->height())
    {
        showMaxRestore();
    }
 }

/////////////////////////////new resize implementation///////////
void MainWindow::updateSizedCursor(const QPoint &gMousePos)
{
    if (isFullScreen() || isMaximized())
    {
        if (isSizedCursor)
        {
            unsetCursor();
            isSizedCursor = false;
        }
        return;
    }

    posMouseMove.recalculate(gMousePos, frameGeometry());

    if(posMouseMove.m_bOnTopLeftEdge || posMouseMove.m_bOnBottomRightEdge)
    {
        setCursor( Qt::SizeFDiagCursor );
        isSizedCursor = true;
    }
    else if(posMouseMove.m_bOnTopRightEdge || posMouseMove.m_bOnBottomLeftEdge)
    {
        setCursor( Qt::SizeBDiagCursor );
        isSizedCursor = true;
    }
    else if(posMouseMove.m_bOnLeftEdge || posMouseMove.m_bOnRightEdge)
    {
        setCursor( Qt::SizeHorCursor );
        isSizedCursor = true;
    }
    else if(posMouseMove.m_bOnTopEdge || posMouseMove.m_bOnBottomEdge)
    {
        setCursor( Qt::SizeVerCursor );
        isSizedCursor = true;
    }
    else
    {
        if (isSizedCursor)
        {
            unsetCursor();
            isSizedCursor = false;
        }
    }
}


void MainWindow::resizeMainWindow(const QPoint &gMousePos)
{
    QRect origRect;

    origRect = frameGeometry();

    int left = origRect.left();
    int top = origRect.top();
    int right = origRect.right();
    int bottom = origRect.bottom();
    //origRect.getCoords(&left, &top, &right, &bottom);

    int minWidth = minimumWidth();
    int minHeight = minimumHeight();

    if (posMousePressed.m_bOnTopLeftEdge)
    {
        left = gMousePos.x();
        top = gMousePos.y();
    }
    else if (posMousePressed.m_bOnBottomLeftEdge)
    {
        left = gMousePos.x();
        bottom = gMousePos.y();
    }
    else if (posMousePressed.m_bOnTopRightEdge)
    {
        right = gMousePos.x();
        top = gMousePos.y();
    }
    else if (posMousePressed.m_bOnBottomRightEdge)
    {
        right = gMousePos.x();
        bottom = gMousePos.y();
    }
    else if (posMousePressed.m_bOnLeftEdge)
    {
        left = gMousePos.x();
    }
    else if (posMousePressed.m_bOnRightEdge)
    {
        right = gMousePos.x();
    }
    else if (posMousePressed.m_bOnTopEdge)
    {
        top = gMousePos.y();
    }
    else if (posMousePressed.m_bOnBottomEdge)
    {
        bottom = gMousePos.y();
    }

    QRect newRect(QPoint(left, top), QPoint(right, bottom));

    if (newRect.isValid())
    {
        if (minWidth > newRect.width())
        {
            if (left != origRect.left())
                newRect.setLeft(origRect.left());
            else
                newRect.setRight(origRect.right());
        }
        if (minHeight > newRect.height())
        {
            if (top != origRect.top())
                newRect.setTop(origRect.top());
            else
                newRect.setBottom(origRect.bottom());
        }
       setGeometry(newRect);

    }
}


void MainWindow::moveTopFrame(const QPoint& gMousePos)
{
    move(gMousePos - posPressedInFrame);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
        case QEvent::MouseMove:
        case QEvent::HoverMove:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::Leave:
        {
           handleSelfEvent(event);
        }
    }
     return QObject::eventFilter(obj, event);
}

void MainWindow::handleSelfEvent(QEvent *event)
{
    switch (event->type())
    {
    default:
        break;
    case QEvent::MouseButtonPress:
        handleMousePressEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseButtonRelease:
        handleMouseReleaseEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseMove:
        handleMouseMoveEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::Leave:
        handleLeaveEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::HoverMove:
        handleHoverMoveEvent(static_cast<QHoverEvent*>(event));
        break;
    }
}

void MainWindow::handleMousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftButtonPressed = true;

        QRect frameRect = frameGeometry();
        posMousePressed.recalculate(event->globalPos(), frameRect);

        posPressedInFrame = event->globalPos() - frameRect.topLeft();
    }
}

void MainWindow::handleMouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftButtonPressed = false;
        posMousePressed.reset();
    }
}

void MainWindow::handleMouseMoveEvent(QMouseEvent *event)
{
    if (isLeftButtonPressed)
    {

        if ( posMousePressed.m_bOnEdges)
        {
            if(!(isMaximized()||isFullScreen())) resizeMainWindow(event->globalPos());
        }
        else if(posPressedInFrame.y()<ptrTitleBar->height())
        {
           moveTopFrame(event->globalPos());
        }
        else if(isAllowAnyDrag) moveTopFrame(event->globalPos());
    }
    else
    {
        updateSizedCursor(event->globalPos());
    }
}

void MainWindow::handleLeaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if (!isLeftButtonPressed)
    {
        unsetCursor();
    }
}

void MainWindow::handleHoverMoveEvent(QHoverEvent *event)
{
   updateSizedCursor(mapToGlobal(event->pos()));
}
