#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "pushbutton.h"
#include "toolbutton.h"

class HeaderBar : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderBar(QWidget *parent = 0);
    ~HeaderBar();

    void updateMaxIcon(bool max = true);
    //void CreateEventFiter();//创建事件过滤器
    //bool eventFilter(QObject *obj, QEvent *event);//事件过滤

signals:
    void signal_menu(QPoint pt);
    void signal_maxrestore();
    //void signal_popupMenu(const QPoint &pos);
private slots:
    void slot_menu();


private:
    QWidget *thisParent;
    QLabel *ptrLabelIcon;

    PushButton *ptrBtnMenu;
    PushButton *ptrBtnMin;
    PushButton *ptrBtnMax;
    PushButton *ptrBtnClose;

    ToolButton *ptrBtnSite;
    ToolButton *ptrBtnDevice;
    ToolButton *ptrBtnCable;
    QHBoxLayout *ptrTitleLayout;
    QHBoxLayout *ptrToolLayout;
    QVBoxLayout *ptrHeaderLayout;
    void CreateWidget();//创建子部件
    void SetWidgetStyle();//设置子部件样式(qss)
    void CreateLayout();  //创建设置布局
};


#endif // HEADERBAR_H
