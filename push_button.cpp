

#include "push_button.h"


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
    QPixmap *pix = new QPixmap(namePixFile);
    btn_width = pix->width()/3;
    btn_height = pix->height();
    setFixedSize(btn_width,btn_height);
    normPix = pix->copy(0,0,btn_width,btn_height);
    enterPix = pix->copy(btn_width,0,btn_width,btn_height);
    pressPix = pix->copy(btn_width*2,0,btn_width,btn_height);
    if(NULL != pix) delete pix;
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
            //pixmap.load(dirPixBase+namePixFile);
            painter.drawPixmap(rect(), normPix);
			break;
		}    
	case ENTER:
		{
            painter.drawPixmap(rect(), enterPix);//pixmap.load(dirPixBase+QString("enter_")+namePixFile);
			break;
		} 
	case PRESS:
		{
            painter.drawPixmap(rect(), pressPix);//pixmap.load(dirPixBase+QString("press_")+namePixFile);
			break;
		}   
	case NOSTATUS:
		{
            painter.drawPixmap(rect(), normPix);//pixmap.load(dirPixBase+namePixFile);
			break;
		}   
	default:
        painter.drawPixmap(rect(), normPix);//pixmap.load(dirPixBase+namePixFile);
	}
	
    //painter.drawPixmap(rect(), pixmap);
}
