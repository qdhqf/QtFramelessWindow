#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent):
    QWidget(parent)
{
<<<<<<< HEAD
     setFixedHeight(20);
     setAutoFillBackground(true);
     QPalette pal;
     QPixmap pix(":/image/header.png");
     pal.setBrush(backgroundRole(),QBrush(pix));
     setPalette(pal);
=======
     setFixedHeight(30);
     setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

>>>>>>> remotes/QtDirectUI/master
}

StatusBar::~StatusBar()
{

}
