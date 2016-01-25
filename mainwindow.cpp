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

    m_pTitleBar = new TitleBar();//创建标题栏
    m_pTitleBar->setStyleSheet("QWidget {border:1px solid black;}");
    m_pToolBar = new ToolBar();//创建工具栏
    m_pToolBar->setStyleSheet("QWidget {border:1px solid black;}");
    m_pContentWidget = new ContentWidget();//创建内容区域
    m_pContentWidget->setStyleSheet("QWidget {border:1px solid black;}");
    m_pStatuBar = new StatuBar();//创建状态栏
    m_pStatuBar->setStyleSheet("QWidget {border:1px solid black;}");
    setStyleSheet("QFrame {background-image:url(:/image/frame.jpg);border:0px solid black;}");

    m_pMainLayout = new QVBoxLayout(this);//创建布局
    //将部件加入到布局中
    m_pMainLayout->addWidget(m_pTitleBar);
    m_pMainLayout->addWidget(m_pToolBar);
    m_pMainLayout->addWidget(m_pContentWidget);
    m_pMainLayout->addWidget(m_pStatuBar);
    //设置间距与边缘空白
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->setContentsMargins(5,5,5,5);

    setMinimumWidth(800);
    setMinimumHeight(600);
    m_bMaxWin = false;
    m_bLeftButtonPressed = false;
 //   m_eDirection=eNone;

    installEventFilter(this);
    connect(m_pTitleBar, SIGNAL(signal_min()), this, SLOT(showMinimized()));
    connect(m_pTitleBar, SIGNAL(signal_maxrestore()), this, SLOT(showMaxRestore()));
    connect(m_pTitleBar, SIGNAL(signal_close()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    setMouseTracking(false);
    setAttribute(Qt::WA_Hover, false);

}
void MainWindow::showMaxRestore()
{
    if(m_bMaxWin)
    {
        this->showNormal();
    }
    else
    {
        this->showMaximized();
    }
    m_bMaxWin = !m_bMaxWin;
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
    if (event->button() == Qt::LeftButton && event->y()<= m_pTitleBar->height())
    {
        if(!m_bMaxWin)
        {
            m_rectRestoreWindow = geometry();
            setGeometry(qApp->desktop()->availableGeometry());
        }
        else
        {
            setGeometry(m_rectRestoreWindow);
        }
        m_bMaxWin = !m_bMaxWin;
    }
 }

/////////////////////////////new resize implementation///////////
void MainWindow::updateCursorShape(const QPoint &gMousePos)
{
    if (isFullScreen() || isMaximized())
    {
        if (m_bCursorShapeChanged)
        {
            unsetCursor();
        }
        return;
    }

    m_moveMousePos.recalculate(gMousePos, frameGeometry());

    if(m_moveMousePos.m_bOnTopLeftEdge || m_moveMousePos.m_bOnBottomRightEdge)
    {
        setCursor( Qt::SizeFDiagCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnTopRightEdge || m_moveMousePos.m_bOnBottomLeftEdge)
    {
        setCursor( Qt::SizeBDiagCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnLeftEdge || m_moveMousePos.m_bOnRightEdge)
    {
        setCursor( Qt::SizeHorCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnTopEdge || m_moveMousePos.m_bOnBottomEdge)
    {
        setCursor( Qt::SizeVerCursor );
        m_bCursorShapeChanged = true;
    }
    else
    {
        if (m_bCursorShapeChanged)
        {
            unsetCursor();
            m_bCursorShapeChanged = false;
        }
    }
}


void MainWindow::resizeTopFrame(const QPoint &gMousePos)
{
    QRect origRect;

    origRect = frameGeometry();

    int left = origRect.left();
    int top = origRect.top();
    int right = origRect.right();
    int bottom = origRect.bottom();
    origRect.getCoords(&left, &top, &right, &bottom);

    int minWidth = minimumWidth();
    int minHeight = minimumHeight();

    if (m_pressedMousePos.m_bOnTopLeftEdge)
    {
        left = gMousePos.x();
        top = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnBottomLeftEdge)
    {
        left = gMousePos.x();
        bottom = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnTopRightEdge)
    {
        right = gMousePos.x();
        top = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnBottomRightEdge)
    {
        right = gMousePos.x();
        bottom = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnLeftEdge)
    {
        left = gMousePos.x();
    }
    else if (m_pressedMousePos.m_bOnRightEdge)
    {
        right = gMousePos.x();
    }
    else if (m_pressedMousePos.m_bOnTopEdge)
    {
        top = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnBottomEdge)
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
    move(gMousePos - m_ptDragPos);
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
        m_bLeftButtonPressed = true;
        //m_bLeftButtonTitlePressed = event->pos().y() < m_moveMousePos.m_nTitleHeight;

        QRect frameRect = frameGeometry();
        m_pressedMousePos.recalculate(event->globalPos(), frameRect);

        m_ptDragPos = event->globalPos() - frameRect.topLeft();
    }
}

void MainWindow::handleMouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPressed = false;
        m_pressedMousePos.reset();
    }
}

void MainWindow::handleMouseMoveEvent(QMouseEvent *event)
{
    if (m_bLeftButtonPressed)
    {
        if ( m_pressedMousePos.m_bOnEdges)
        {
            resizeTopFrame(event->globalPos());
        }
    }
    else
    {
        updateCursorShape(event->globalPos());
    }
}

void MainWindow::handleLeaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if (!m_bLeftButtonPressed)
    {
        unsetCursor();
    }
}

void MainWindow::handleHoverMoveEvent(QHoverEvent *event)
{
  updateCursorShape(mapToGlobal(event->pos()));
}
