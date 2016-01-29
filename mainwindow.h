#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QLayout>

#define VALUE_DIS 5
#define TITLE_H  30
#define HEADER_H 80

class HeaderBar;
class ContentWidget;
class StatusBar;

class CursorPosCalculator
{
public:
    explicit CursorPosCalculator();
    void reset();
    void recalculate(const QPoint &globalMousePos, const QRect &frameRect);

public:
    bool isOnEdge              : true;
    bool isOnLeftEdge           : true;
    bool isOnRightEdge          : true;
    bool isOnTopEdge            : true;
    bool isOnBottomEdge         : true;
    bool isOnLeftTopCorner      : true;
    bool isOnLeftBottomCorner     : true;
    bool isOnRightTopCorner       : true;
    bool isOnRightBottomCorner    : true;
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
    bool event(QEvent *event);

private:
    HeaderBar       *ptrHeaderBar;
    ContentWidget   *ptrContentWidget;
    StatusBar        *ptrStatusBar;
    QVBoxLayout     *ptrMainLayout;


 //Resize Move handling related staffs
    void updateSizedCursor(const QPoint &gMousePos);
    void resizeMainWindow(const QPoint &gMousePos);
    void moveTopFrame(const QPoint& gMousePos);
    CursorPosCalculator posMousePressed;
    CursorPosCalculator posMouseMove;
    bool isLeftButtonPressed;
    bool isSizedCursor;
    bool isOnlyHeadDrag;

    double xfactor;
    double yfactor;

    QPoint posPressedInFrame;//m_ptDragPos;
    void handleMouseDblClickEvent(QMouseEvent *event);
    void handleMousePressEvent(QMouseEvent *event);
    void handleMouseReleaseEvent(QMouseEvent *event);
    void handleMouseMoveEvent(QMouseEvent *event);
    void handleLeaveEvent(QEvent *event);
    void handleHoverMoveEvent(QHoverEvent *event);
};



#endif // MAINWINDOW_H

