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
    this->pathPix = origPix;
    setFixedSize(QPixmap(pathPix).size());
    namesec = pathPix.split(".");
}

void PushButton::switchPix(QString newPix)
{
    this->pathPix = newPix;
    namesec.clear();
    namesec = pathPix.split(".");
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
            //pixmap =selfPix->copy(0,0,btn_width,btn_height);
            pixmap.load(pathPix);
			break;
		}    
	case ENTER:
		{
            //pixmap =selfPix->copy(btn_width,0,btn_width*2,btn_height);
            pixmap.load(namesec[0] + QString("_enter.")+namesec[1]);
			break;
		} 
	case PRESS:
		{
            //pixmap =selfPix->copy(btn_width*2,0,btn_width*3,btn_height);
            pixmap.load(namesec[0] + QString("_press.")+namesec[1]);
			break;
		}   
	case NOSTATUS:
		{
            //pixmap =selfPix->copy(0,0,btn_width,btn_height);
            pixmap.load(pathPix);
			break;
		}   
	default:
        //pixmap =selfPix->copy(0,0,btn_width,btn_height);
        pixmap.load(pathPix);
	}
	
	painter.drawPixmap(rect(), pixmap);
}
