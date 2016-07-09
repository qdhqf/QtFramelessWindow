#ifndef NETPLANVIEW_H
#define NETPLANVIEW_H


#include <QtWidgets>

class NetPlanView : public QWidget
{
    Q_OBJECT
public:
    explicit NetPlanView(QWidget *parent = 0);

signals:

public slots:

private:
    void fillToolBar();
private:
   QToolBar *planToolBar;
};

#endif // NETPLANVIEW_H
