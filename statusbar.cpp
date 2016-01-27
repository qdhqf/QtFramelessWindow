#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent):
    QWidget(parent)
{
     setFixedHeight(30);
     setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

}

StatusBar::~StatusBar()
{

}
