# pragma warning (disable:4819)

#include "tool_button.h"

ToolButton::ToolButton(QString namePix, QWidget *parent)
	:QToolButton(parent)
{
    QPalette text_palette = palette();//设置文本颜色
	text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
	setPalette(text_palette);


    QFont &text_font = const_cast<QFont &>(font());//设置文本粗体
	text_font.setWeight(QFont::Bold);

	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    QPixmap pixmap(namePix);//设置图标
	setIcon(pixmap);
	setIconSize(pixmap.size());


    setFixedSize(pixmap.width()+40, pixmap.height()+20);//设置大小
	setAutoRaise(true);
	setObjectName("transparentToolButton");

	mouse_over = false;
	mouse_press = false;
}

ToolButton::~ToolButton()
{

}

void ToolButton::enterEvent(QEvent *)
{
	mouse_over = true;
}

void ToolButton::leaveEvent(QEvent *)
{
	mouse_over = false;
}

void ToolButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
        mouse_press = true;
        update();
        //emit clicked();
	}
}

void ToolButton::mouseReleaseEvent(QMouseEvent *event)
{

    if(mouse_press  && this->rect().contains(event->pos())) //若点击鼠标左键
    {
        mouse_press = false;
        update();
        emit clicked();
    }
}

void ToolButton::setMousePress(bool mouse_press)
{
	this->mouse_press = mouse_press;
	update();
}

void ToolButton::paintEvent(QPaintEvent *event)
{
	if(mouse_over)
	{
        painterInfo(0, 100, 150); //绘制鼠标移到按钮上的按钮效果
	}
	else
	{
		if(mouse_press)
		{
            painterInfo(0, 100, 150);
		}
	}

	QToolButton::paintEvent(event);
}

void ToolButton::painterInfo(int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(230, 230, 230, top_color));
    linear.setColorAt(0.5, QColor(230, 230,230, middle_color));
    linear.setColorAt(1, QColor(230, 230, 230, bottom_color));
	painter.setBrush(linear);
	painter.drawRect(rect());
}
