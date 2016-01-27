#include "contentwidget.h"

ContentWidget::ContentWidget(QWidget *parent):
    QWidget(parent)
{
     setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     setAutoFillBackground(true);
     QPalette pal;
     QPixmap pix(":/image/frame.jpg");
     pal.setBrush(backgroundRole(),QBrush(pix));
     setPalette(pal);
}

ContentWidget::~ContentWidget()
{

}

