#ifndef PORTLINKITEM_H
#define PORTLINKITEM_H
#include <QGraphicsLineItem>

#include "nodeitem.h"
QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

class PortLinkItem : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    PortLinkItem(NodeItem *startItem, NodeItem *endItem,
      QGraphicsItem *parent = 0);

    int type() const Q_DECL_OVERRIDE { return Type; }
   // QRectF boundingRect() const Q_DECL_OVERRIDE;
    //QPainterPath shape() const Q_DECL_OVERRIDE;
    void setColor(const QColor &color) { myColor = color; }
    NodeItem *startItem() const { return myStartItem; }
    NodeItem *endItem() const { return myEndItem; }

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    NodeItem *myStartItem;
    NodeItem *myEndItem;
    QColor myColor;
    QPolygonF PortLinkItemHead;
};
#endif // PORTLINKITEM_H
