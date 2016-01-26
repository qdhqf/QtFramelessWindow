#include "mainwindow.h"
#include "headerbar.h"
#include "contentwidget.h"
#include "statusbar.h"


//////////////Begin CursorPosCalculator//////////////


/***** CursorPosCalculator *****/
CursorPosCalculator::CursorPosCalculator()
{
    reset();
}

void CursorPosCalculator::reset()
{
    isOnEdge = false;
    isOnLeftEdge = false;
    isOnRightEdge = false;
    isOnTopEdge = false;
    isOnBottomEdge = false;
    isOnLeftTopCorner = false;
    isOnLeftBottomCorner = false;
    isOnRightTopCorner  = false;
    isOnRightBottomCorner = false;
}

void CursorPosCalculator::recalculate(const QPoint &gMousePos, const QRect &frameRect)
{
    int globalMouseX = gMousePos.x();
    int globalMouseY = gMousePos.y();

    int frameX = frameRect.x();
    int frameY = frameRect.y();

    int frameWidth = frameRect.width();
    int frameHeight = frameRect.height();

    isOnLeftEdge = (globalMouseX >= frameX &&
                  globalMouseX <= frameX + VALUE_DIS );


    isOnRightEdge = (globalMouseX >= frameX + frameWidth - VALUE_DIS &&
                   globalMouseX <= frameX + frameWidth);

    isOnTopEdge = (globalMouseY >= frameY &&
                 globalMouseY <= frameY + VALUE_DIS );

    isOnBottomEdge = (globalMouseY >= frameY + frameHeight - VALUE_DIS &&
                    globalMouseY <= frameY + frameHeight);

    isOnLeftTopCorner = isOnTopEdge && isOnLeftEdge;
    isOnLeftBottomCorner = isOnBottomEdge && isOnLeftEdge;
    isOnRightTopCorner = isOnTopEdge && isOnRightEdge;
    isOnRightBottomCorner = isOnBottomEdge && isOnRightEdge;

    isOnEdge = isOnLeftEdge || isOnRightEdge || isOnTopEdge || isOnBottomEdge;
}
//////////////End CursorPosCalculator//////////////


MainWindow::MainWindow(QWidget *parent)
    : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
  //setWindowFlags(Qt::CustomizeWindowHint);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);

    ptrHeaderBar = new HeaderBar();//创建标题栏
    ptrHeaderBar->setStyleSheet("QWidget {border:1px solid black;}");

    ptrContentWidget = new ContentWidget();//创建内容区域
    ptrContentWidget->setStyleSheet("QWidget {border:1px solid black;}");
    ptrStatusBar = new StatusBar();//创建状态栏
    ptrStatusBar->setStyleSheet("QWidget {border:1px solid black;}");

    setStyleSheet("QFrame {background-image:url(:/image/frame.jpg);border:0px solid black;}");

    ptrMainLayout = new QVBoxLayout(this);//创建布局

    ptrMainLayout->addWidget(ptrHeaderBar);//将部件加入到布局中
    ptrMainLayout->addWidget(ptrContentWidget);
    ptrMainLayout->addWidget(ptrStatusBar);
    //设置间距与边缘空白
    ptrMainLayout->setSpacing(0);
    ptrMainLayout->setContentsMargins(VALUE_DIS,VALUE_DIS,VALUE_DIS,VALUE_DIS);

    setMinimumWidth(800);
    setMinimumHeight(600);

    isLeftButtonPressed = false;
    isSizedCursor = false;
    isAllowAnyDrag = false;

    installEventFilter(this);
    connect(ptrHeaderBar, SIGNAL(signal_min()), this, SLOT(showMinimized()));
    connect(ptrHeaderBar, SIGNAL(signal_maxrestore()), this, SLOT(showMaxRestore()));
    connect(ptrHeaderBar, SIGNAL(signal_close()), this, SLOT(close()));
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
    if (event->button() == Qt::LeftButton && event->y()<= ptrHeaderBar->height())
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

    if(posMouseMove.isOnLeftTopCorner || posMouseMove.isOnRightBottomCorner)
    {
        setCursor( Qt::SizeFDiagCursor );
        isSizedCursor = true;
    }
    else if(posMouseMove.isOnRightTopCorner || posMouseMove.isOnLeftBottomCorner)
    {
        setCursor( Qt::SizeBDiagCursor );
        isSizedCursor = true;
    }
    else if(posMouseMove.isOnLeftEdge || posMouseMove.isOnRightEdge)
    {
        setCursor( Qt::SizeHorCursor );
        isSizedCursor = true;
    }
    else if(posMouseMove.isOnTopEdge || posMouseMove.isOnBottomEdge)
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

    if (posMousePressed.isOnLeftTopCorner)
    {
        left = gMousePos.x();
        top = gMousePos.y();
    }
    else if (posMousePressed.isOnLeftBottomCorner)
    {
        left = gMousePos.x();
        bottom = gMousePos.y();
    }
    else if (posMousePressed.isOnRightTopCorner)
    {
        right = gMousePos.x();
        top = gMousePos.y();
    }
    else if (posMousePressed.isOnRightBottomCorner)
    {
        right = gMousePos.x();
        bottom = gMousePos.y();
    }
    else if (posMousePressed.isOnLeftEdge)
    {
        left = gMousePos.x();
    }
    else if (posMousePressed.isOnRightEdge)
    {
        right = gMousePos.x();
    }
    else if (posMousePressed.isOnTopEdge)
    {
        top = gMousePos.y();
    }
    else if (posMousePressed.isOnBottomEdge)
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

        if ( posMousePressed.isOnEdge)
        {
            if(!(isMaximized()||isFullScreen())) resizeMainWindow(event->globalPos());
        }
        else
            if(posPressedInFrame.y()<ptrHeaderBar->height())
            {
                if(isMaximized()||isFullScreen())
                 {
                    this->showNormal();
                }
                else
                {
                    moveTopFrame(event->globalPos());
                }

            }
            else
                if(isAllowAnyDrag)
                {
                    if(isMaximized()||isFullScreen())
                    {
                        this->showNormal();
                    }
                    else
                    {
                        moveTopFrame(event->globalPos());
                    }
                 }
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
