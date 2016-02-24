
#include "mainwindow.h"
#include "headerbar.h"
#include "statusbar.h"
#include "defs.h"
#include "tabwidget.h"
#include "mainmenu.h"

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

    ptrHeaderBar = new HeaderBar(this);//创建标题栏
    ptrStatusBar = new StatusBar(this);//创建状态栏
    QString msg = "Ready";
    ptrStatusBar->setMessage(msg);

    ptrMainLayout = new QVBoxLayout(this);//创建布局
    ptrMainLayout->addWidget(ptrHeaderBar);//将部件加入到布局中
    QSplitter *mainSplitter = new QSplitter(this);
    TabWidget *t1 = new TabWidget(this);
    //TabWidget *t2 = new TabWidget(this);
    QGraphicsView *v = new QGraphicsView(this);
    mainSplitter->addWidget(t1);
    mainSplitter->addWidget(v);
    ptrMainLayout->addWidget(mainSplitter);
    ptrMainLayout->addWidget(ptrStatusBar);
    //设置间距与边缘空白
    ptrMainLayout->setSpacing(0);
    ptrMainLayout->setContentsMargins(VALUE_DIS,VALUE_DIS,VALUE_DIS,VALUE_DIS);

    setMinimumWidth(800);
    setMinimumHeight(600);

    isLeftButtonPressed = false;
    isSizedCursor = false;
    isOnlyHeadDrag = true;

    xfactor = 1.0; yfactor = 1.0;
    connect(ptrHeaderBar, SIGNAL(signal_menu(QPoint)), this, SLOT(showMenu(QPoint)));
    connect(ptrHeaderBar, SIGNAL(signal_maxrestore()), this, SLOT(showMaxRestore()));

}

MainWindow::~MainWindow()
{
    setMouseTracking(false);
    setAttribute(Qt::WA_Hover, false);

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
        ptrHeaderBar->updateMaxIcon(false);
    }
    else
    {
        this->showMaximized();
        ptrHeaderBar->updateMaxIcon();
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

bool MainWindow::event(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::MouseButtonDblClick:
             {
                handleMouseDblClickEvent(static_cast<QMouseEvent*>(event));
                break;
             }
        case QEvent::MouseMove:
            {
                handleMouseMoveEvent(static_cast<QMouseEvent*>(event));
                break;
            }
        case QEvent::HoverMove:
            {
                handleHoverMoveEvent(static_cast<QHoverEvent*>(event));
                break;
            }
        case QEvent::MouseButtonPress:
           {
                handleMousePressEvent(static_cast<QMouseEvent*>(event));
                break;
           }
        case QEvent::MouseButtonRelease:
           {
                handleMouseReleaseEvent(static_cast<QMouseEvent*>(event));
                break;
           }
        case QEvent::Leave:
           {
                handleLeaveEvent(static_cast<QMouseEvent*>(event));
                break;
            }
    }
     return QFrame::event(event);//QFrame::eventFilter(obj, event);
}

//鼠标双击事件
void MainWindow::handleMouseDblClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y()<= ptrHeaderBar->height())
    {
        showMaxRestore();
        xfactor = 1.0;
        yfactor = 1.0;
    }
 }

void MainWindow::handleMousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftButtonPressed = true;
        xfactor = 1.0;
        yfactor = 1.0;
        QRect frameRect = frameGeometry();
        posMousePressed.recalculate(event->globalPos(), frameRect);

        posPressedInFrame = event->globalPos() - frameRect.topLeft();
        if(isMaximized()||isFullScreen())
        {
            xfactor = 1.0*posPressedInFrame.x()/frameRect.width();
            yfactor = 1.0*posPressedInFrame.y()/frameRect.height();
        }
        // debug message
        QString msg;
        msg.setNum(xfactor);
        msg += ",";
        msg += msg.number(yfactor);
        ptrStatusBar->setMessage(msg);
    }
}


void MainWindow::handleMouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftButtonPressed = false;
        posMousePressed.reset();
        xfactor = 1.0;
        yfactor = 1.0;
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
                    if(isMaximized()||isFullScreen())
                    this->showMaxRestore();
                 }
                else
                {
                    if(1.0 == xfactor)
                    {
                        moveTopFrame(event->globalPos());
                    }
                    else
                    {
                       QRect frameRect = frameGeometry();
                       posPressedInFrame.setX(frameRect.width()*xfactor);
                       moveTopFrame(event->globalPos());
                       xfactor = 1.0;
                    }
                }

            }
            else
                if(!isOnlyHeadDrag)
                {
                    if(isMaximized()||isFullScreen())
                    {
                        this->showMaxRestore();
                    }
                    else
                    {
                        if(1.0 == xfactor)
                        {
                            moveTopFrame(event->globalPos());
                        }
                        else
                        {
                           QRect frameRect = frameGeometry();
                           posPressedInFrame.setX(frameRect.width()*xfactor);
                           posPressedInFrame.setY(frameRect.height()*yfactor);
                           moveTopFrame(event->globalPos());
                           xfactor = 1.0;
                        }
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
        isSizedCursor = false;
    }
}

void MainWindow::handleHoverMoveEvent(QHoverEvent *event)
{
    updateSizedCursor(mapToGlobal(event->pos()));
}
