#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QtWidgets>
#include <QtCore>
#include <QtGui>


class HeaderBar : public QWidget
{
    Q_OBJECT

public:
    //枚举，按钮状态
    enum eBtnMoustState{
         eBtnStateNone,//无效
         eBtnStateDefault,//默认值(如按钮初始显示)
         eBtnStateHover,//鼠标移到按钮上状态
         eBtnStatePress//鼠标按下按钮时状态
     };


public:
    explicit HeaderBar(QWidget *parent = 0);
    ~HeaderBar();

    void CreateWidget();//创建子部件
    void SetWidgetStyle();//设置子部件样式(qss)
    void CreateLayout();  //创建设置布局
    const QString GetBtnImagePath(QToolButton *pBtn,bool bInit/*=false*/);//获得图片路径(固定值)
    void CreateEventFiter();//创建事件过滤器
    bool eventFilter(QObject *obj, QEvent *event);//事件过滤
    void paintEvent(QPaintEvent *event);
signals:
    void signal_min();
    void signal_maxrestore();
    void signal_close();
    void signal_popupMenu(const QPoint &pos);

public slots:  
    void slot_btnpress();
    void slot_btnclick();//槽函数--slot_btnclick

private:
    QLabel *ptrLabelIcon;

    QToolButton *ptrBtnMenu;
    QToolButton *ptrBtnMin;
    QToolButton *ptrBtnMax;
    QToolButton *ptrBtnClose;
    QHBoxLayout *ptrTitleLayout;
    QHBoxLayout *ptrToolLayout;
    QVBoxLayout *ptrHeaderLayout;
    int m_windowState;

    void SetBtnIcon(QToolButton *pBtn,eBtnMoustState state,bool bInit=false);
};


#endif // HEADERBAR_H
