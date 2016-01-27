#include "push_button.h"

QString PushButton::dirPixBase = ":/image/sysButton/";

PushButton::PushButton(QWidget *parent)
	:QPushButton(parent)
{	
	status = NORMAL;
	mouse_press = false;
}

PushButton::~PushButton()
{

}

void PushButton::setPix(QString origPix)
{
    this->namePixFile = origPix;
    setFixedSize(QPixmap(dirPixBase+namePixFile).size());
}

void PushButton::switchPix(QString newPix)
{
    this->namePixFile = newPix;
}

void PushButton::enterEvent(QEvent *)
{
	status = ENTER;
	update();
}

void PushButton::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton) //若点击鼠标左键
	{
		mouse_press = true;
		status = PRESS;
		update();
	}
}

void PushButton::mouseReleaseEvent(QMouseEvent *event)
{

    if(mouse_press  && this->rect().contains(event->pos())) //若点击鼠标左键
	{
		mouse_press = false;
		status = ENTER;
		update();
		emit clicked();
	}
}

void PushButton::leaveEvent(QEvent *)
{
	status = NORMAL;
	update();
}

void PushButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

    switch(status)
	{
	case NORMAL:
		{
            pixmap.load(dirPixBase+namePixFile);
			break;
		}    
	case ENTER:
		{
            pixmap.load(dirPixBase+QString("enter_")+namePixFile);
			break;
		} 
	case PRESS:
		{
            pixmap.load(dirPixBase+QString("press_")+namePixFile);
			break;
		}   
	case NOSTATUS:
		{
            pixmap.load(dirPixBase+namePixFile);
			break;
		}   
	default:
        pixmap.load(dirPixBase+namePixFile);
	}
	
	painter.drawPixmap(rect(), pixmap);
}
