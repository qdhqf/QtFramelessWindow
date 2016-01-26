#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtWidgets>
#include <QtCore>
#include <QtGui>


class TitleBar : public QWidget
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
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

    //创建子部件
    void CreateWidget();

    //设置子部件样式(qss)
    void SetWidgetStyle();



    //创建设置布局
    void CreateLayout();

    //获得图片路径(固定值)
    const QString GetBtnImagePath(QToolButton *pBtn,bool bInit/*=false*/);

    //创建事件过滤器
    void CreateEventFiter();

    //事件过滤
    bool eventFilter(QObject *obj, QEvent *event);
protected:
    //鼠标按下事件
   // virtual void mousePressEvent(QMouseEvent *event);
    //鼠标移动事件
   // virtual void mouseMoveEvent(QMouseEvent *event);
    //鼠标释放事件
   // virtual void mouseReleaseEvent(QMouseEvent *event);
    //鼠标双击事件

signals:
    void signal_min();
    void signal_maxrestore();
    void signal_close();
    void signal_popupMenu(const QPoint &pos);

public slots:
    //槽函数--slot_btnclick
    void slot_btnpress();
    void slot_btnclick();

private:
    QLabel *m_pLabelIcon;

    QToolButton *m_pBtnMenu;
    QToolButton *m_pBtnMin;
    QToolButton *m_pBtnMax;
    QToolButton *m_pBtnClose;
    QHBoxLayout *m_pLayout;
    bool m_bLeftButtonPress;
    QPoint m_ptPress;
    QPoint m_ptMove;
    QWidget *m_parent;
    QFrame *m_bkFrame;
    int m_windowState;

    void SetBtnIcon(QToolButton *pBtn,eBtnMoustState state,bool bInit=false);
};




#endif // TITLEBAR_H
