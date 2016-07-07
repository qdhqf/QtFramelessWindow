#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent):
    QWidget(parent)
{
     setFixedHeight(25);
     //setStyleSheet("QWidget{ border: none; padding: 0px; }");
     setAutoFillBackground(true);
     QPalette pal;
     QPixmap pix(":/image/status.png");
     pal.setBrush(backgroundRole(),QBrush(pix));
     setPalette(pal);

     ptrMsg = new QLabel(this);
     ptrMsg->setFixedWidth(300); //for testing
     ptrMsg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     ptrMsg->setStyleSheet("QLabel{margin-left:10px;color:white}QLabel:hover{color:#00AA00;}");

}

StatusBar::~StatusBar()
{

}

void StatusBar::setMessage(QString &msg)
{
  ptrMsg->setText(msg);
}
