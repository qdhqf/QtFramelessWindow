#include "nodeitem.h"
#include "portlinkitem.h"

NodeItem::NodeItem()
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    setPixmap(QPixmap(":/image/NodeIcon/OTN.png"));
    nodeText =  QStringLiteral("ITMC(中蒙)-N-二连浩特廉租楼-H-OTM/6853-ITMC(中蒙)-N-二连浩特廉租楼-H-OTM");
}

void NodeItem::setMyText(QString &text)
{
    nodeText = text;
}

QRectF NodeItem::boundingRect() const
{
    QRect rect = this->pixmap().rect();
    return QRectF(-10-rect.width()/2.0,-rect.height()/2.0,rect.width()+20,rect.height()+50);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)
    QPixmap pixmap = this->pixmap();
    QRect rect = pixmap.rect();

    painter->drawPixmap(-rect.width()/2.0,-rect.height()/2.0,pixmap);


    //print name,calculate the text's heigh & width for center layout
    QPen pen(Qt::black);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    QFont font("SimSun",10, QFont::Normal);
    painter->setFont(font);

    QFontMetrics fm(font);
    QString str = fm.elidedText(nodeText, /*Qt::TextElideMode*/Qt::ElideRight, 3*(rect.width()+20)-10);
    /*
    enum Qt::TextElideMode
            Constant	Value	Description
            Qt::ElideLeft	0	The ellipsis should appear at the beginning of the text.
            Qt::ElideRight	1	The ellipsis should appear at the end of the text.
            Qt::ElideMiddle	2	The ellipsis should appear in the middle of the text.
            Qt::ElideNone	3	Ellipsis should NOT appear in the text.*/
    painter->drawText(QRectF(-10-rect.width()/2.0,rect.height()/2.0+5,rect.width()+20,45),Qt::AlignLeft|Qt::TextWrapAnywhere/*Qt::TextWordWrap*/,str);

 /*   if (option->state & QStyle::State_Sunken)
    {
        QRectF rect1 = boundingRect();
        //QPen pen(Qt::darkGreen);
        painter->setPen(QPen(Qt::darkGreen));
    }else
    {

    }*/
}


// 鼠标按下事件处理函数，设置被点击的图形项获得焦点，并改变光标外观
void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    qDebug("************MyItem::mousePressEvent*****************");
    setFocus();
    setCursor(Qt::ClosedHandCursor);
}

// 键盘按下事件处理函数，判断是否是向下方向键，如果是，则向下移动图形项
void NodeItem::keyPressEvent(QKeyEvent *event)
{
    qDebug("************MyItem::keyPressEvent*****************");
    if(event->key() == Qt::Key_Down)
        moveBy(0, 10);
}

// 悬停事件处理函数，设置光标外观和提示
void NodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
     Q_UNUSED(event)
    qDebug("************MyItem::hoverEnterEvent*****************");
    setCursor(Qt::OpenHandCursor);
    setToolTip(nodeText);
}

void NodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    qDebug("************MyItem::hoverLeaveEvent*****************");
    setCursor(Qt::ArrowCursor);
}


// 右键菜单事件处理函数，为图形项添加一个右键菜单
void NodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *moveAction = menu.addAction("move back");
    QAction *actAction = menu.addAction("test");
    QAction *selectedAction = menu.exec(event->screenPos());
    if(selectedAction == moveAction) {
        setPos(0, 0);
    }
     Q_UNUSED(actAction)
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("************MyItem::mouseMoveEvent*****************");
    QGraphicsItem::mouseMoveEvent(event);
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (PortLinkItem *link, links) {
            link->updatePosition();
        }
    }

    return value;
}
void NodeItem::addLink(PortLinkItem *link)
{
    links.append(link);
}
