#ifndef NetResView_H
#define NetResView_H


#include <QtWidgets>

class NetResView : public QWidget
{
    Q_OBJECT
public:
    explicit NetResView(QWidget *parent = 0);

signals:

public slots:

private:
    void fillToolBar();
private:
   QToolBar *resToolBar;
};

#endif // NetResView_H
