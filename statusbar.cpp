#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent):
    QWidget(parent)
{
     setFixedHeight(20);
     setAutoFillBackground(true);
     QPalette pal;
     QPixmap pix(":/image/header.png");
     pal.setBrush(backgroundRole(),QBrush(pix));
     setPalette(pal);
}

StatusBar::~StatusBar()
{

}
