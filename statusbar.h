#ifndef STATUSBAR_H
#define STATUSBAR_H
#include <QtWidgets>

class StatusBar:public QWidget
{
     Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = 0);
    ~StatusBar();
};
#endif // STATUSBAR_H
