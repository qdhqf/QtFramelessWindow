#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "pushbutton.h"
#include "tabbar.h"

class HeaderBar : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderBar(QWidget *parent = 0);
    ~HeaderBar();

    void updateMaxIcon(bool max = true);

signals:
    void signal_menu(QPoint pt);
    void signal_maxrestore();
    void sigTabClicked(int index);

private slots:
    void slot_menu();
    void slot_sigTabClicked(int index);

private:
    QWidget *thisParent;
    QLabel *ptrLabelIcon;
    TabBar *tabBar;
    PushButton *ptrBtnMenu;
    PushButton *ptrBtnMin;
    PushButton *ptrBtnMax;
    PushButton *ptrBtnClose;

    QHBoxLayout *ptrTitleLayout;

    void CreateWidget();//创建子部件
    void SetWidgetStyle();//设置子部件样式(qss)
    void CreateLayout();  //创建设置布局
};


#endif // HEADERBAR_H
