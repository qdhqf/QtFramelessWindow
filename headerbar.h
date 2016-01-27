#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "push_button.h"

class HeaderBar : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderBar(QWidget *parent = 0);
    ~HeaderBar();

    void CreateWidget();//创建子部件
    void SetWidgetStyle();//设置子部件样式(qss)
    void CreateLayout();  //创建设置布局
    const QString GetBtnImagePath(QToolButton *pBtn,bool bInit/*=false*/);//获得图片路径(固定值)
    //void CreateEventFiter();//创建事件过滤器
    //bool eventFilter(QObject *obj, QEvent *event);//事件过滤

signals:
    void signal_min();
    void signal_maxrestore();
    void signal_close();
    //void signal_popupMenu(const QPoint &pos);

public slots:  
    void slot_btnpress();
    void slot_btnclick();//槽函数--slot_btnclick

private:
    QLabel *ptrLabelIcon;

    PushButton *ptrBtnMenu;
    PushButton *ptrBtnMin;//QToolButton *ptrBtnMin;
    PushButton *ptrBtnMax;//QToolButton *ptrBtnMax;
    PushButton *ptrBtnClose;//QToolButton *ptrBtnClose;
    QHBoxLayout *ptrTitleLayout;
    QHBoxLayout *ptrToolLayout;
    QVBoxLayout *ptrHeaderLayout;
};


#endif // HEADERBAR_H
