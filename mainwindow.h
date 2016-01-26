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

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

public slots:
    void showMaxRestore();
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void handleSelfEvent(QEvent *event);
private:
    TitleBar        *ptrTitleBar;//*m_pTitleBar;
    ToolBar         *ptrToolBar;//*m_pToolBar;
    ContentWidget   *ptrContentWidget;//*m_pContentWidget;
    StatuBar        *ptrStatuBar;//*m_pStatuBar;
    QVBoxLayout     *ptrMainLayout;//*m_pMainLayout;


 //Resize Move handling related staffs
    void updateSizedCursor(const QPoint &gMousePos);  //updateCursorShape
    void resizeMainWindow(const QPoint &gMousePos);//resizeTopFrame
    void moveTopFrame(const QPoint& gMousePos);
    CursorPosCalculator posMousePressed;
    CursorPosCalculator posMouseMove;
    bool isLeftButtonPressed;
    bool isSizedCursor;
    bool isAllowAnyDrag;

    QPoint posPressedInFrame;//m_ptDragPos;
    void handleMousePressEvent(QMouseEvent *event);
    void handleMouseReleaseEvent(QMouseEvent *event);
    void handleMouseMoveEvent(QMouseEvent *event);
    void handleLeaveEvent(QEvent *event);
    void handleHoverMoveEvent(QHoverEvent *event);
};



#endif // MAINWINDOW_H

