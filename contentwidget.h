#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H
#include <QtWidgets>

class ContentWidget:public QWidget
{
    Q_OBJECT
public:
   explicit ContentWidget(QWidget *parent = 0);
   ~ContentWidget();
};
#endif // CONTENTWIDGET_H
