#include "nodeitem.h"

NodeItem::NodeItem()
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    pix = new QGraphicsPixmapItem(QPixmap(":/image/NodeIcon/OTN.png"));
    pix->setPos(0.0,-0.5*pix->boundingRect().height());
    text = new QGraphicsTextItem("Chinese is not supported");
    text->setTextWidth(2*pix->boundingRect().width());
    text->setPos(-0.5*pix->boundingRect().width(),text->boundingRect().height());
}

QRectF NodeItem::boundingRect() const
{
   /* qreal adjust = 0.5;
    return QRectF(-10 - adjust, -10 - adjust,
                  50 + adjust, 50 + adjust);*/
    return QRectF(pix->boundingRect()) ;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
  pix->paint(painter,option,widget);
  text->paint(painter,option,widget);
}

