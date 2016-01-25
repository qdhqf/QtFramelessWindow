#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QLayout>
#define VALUE_DIS 5
#define TITLE_H  30
class TitleBar;
class ToolBar;
class ContentWidget;
class StatuBar;

class CursorPosCalculator
{
public:
    explicit CursorPosCalculator();
    void reset();
    void recalculate(const QPoint &globalMousePos, const QRect &frameRect);

public:
    bool m_bOnEdges              : true;
    bool m_bOnLeftEdge           : true;
    bool m_bOnRightEdge          : true;
    bool m_bOnTopEdge            : true;
    bool m_bOnBottomEdge         : true;
    bool m_bOnTopLeftEdge        : true;
    bool m_bOnBottomLeftEdge     : true;
    bool m_bOnTopRightEdge       : true;
    bool m_bOnBottomRightEdge    : true;

    static int m_nBorderWidth;
    static int m_nTitleHeight;
};


class MainWindow : public QFrame
{
    Q_OBJECT
/*    enum enum_Direction
    {
        eNone,
        eTop = 1,
        eRight =2 ,
        eBottom =4,
        eLeft = 8,
        eTopRight = eTop + eRight,
        eRightBottom = eRight + eBottom,
        eBottomLeft = eBottom + eLeft,
        eLeftTop = eLeft + eTop
    };*/

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

public slots:
    void showMaxRestore();
protected:
    /*void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);*/
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void handleSelfEvent(QEvent *event);
private:
    TitleBar        *m_pTitleBar;
    ToolBar         *m_pToolBar;
    ContentWidget   *m_pContentWidget;
    StatuBar        *m_pStatuBar;
    QVBoxLayout     *m_pMainLayout;


//    enum_Direction   m_eDirection;
    bool             m_bMaxWin;
    QRect            m_rectRestoreWindow;

//    void            SetCursorStyle(enum_Direction direction);
//    enum_Direction MainWindow::PointValid(int nXRelative,int nYRelative);
//    void SetDrayMove(int nXGlobal,int nYGlobal,enum_Direction direction);

 //Resize Move handling related staffs
    void updateCursorShape(const QPoint &gMousePos);
    void resizeTopFrame(const QPoint &gMousePos);
    void moveTopFrame(const QPoint& gMousePos);
    CursorPosCalculator m_pressedMousePos;
    CursorPosCalculator m_moveMousePos;
    bool m_bLeftButtonPressed;
    bool m_bCursorShapeChanged;
    //bool m_bLeftButtonTitlePressed;
    QPoint m_ptDragPos;
    void handleMousePressEvent(QMouseEvent *event);
    void handleMouseReleaseEvent(QMouseEvent *event);
    void handleMouseMoveEvent(QMouseEvent *event);
    void handleLeaveEvent(QEvent *event);
    void handleHoverMoveEvent(QHoverEvent *event);
};



#endif // MAINWINDOW_H

