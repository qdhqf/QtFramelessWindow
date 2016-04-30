#include "portlinkitem.h"

#include <math.h>

#include <QPen>
#include <QPainter>

const qreal Pi = 3.14;


PortLinkItem::PortLinkItem(NodeItem *startItem, NodeItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
{
    myStartItem = startItem;
    myEndItem = endItem;
    updatePosition();
    startItem->addLink(this);
    endItem->addLink(this);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setZValue(-100.0);
    setSelected(false);
}

/*QRectF PortLinkItem::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}*/

/*QPainterPath PortLinkItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(PortLinkItemHead);
    return path;
}*/

void PortLinkItem::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setSelected(false);
    setLine(line);
}


void PortLinkItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *moveAction = menu.addAction(QStringLiteral("查看相关电路"));
    QAction *actAction = menu.addAction(QStringLiteral("属性"));
    QAction *selectedAction = menu.exec(event->screenPos());
    if(selectedAction == moveAction) {
        setPos(0, 0);
    }
    setSelected(true);
     Q_UNUSED(actAction)
}

void PortLinkItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    qDebug("************PortLinkItem::mousePressEvent*****************");
    setFocus();
    //setCursor(Qt::ClosedHandCursor);
    setSelected(true);
    update();
}


void PortLinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{

    QPen myPen = pen();
    myPen.setColor(myColor);
//    qreal PortLinkItemSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);

 /*
    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
   QPolygonF endPolygon = myEndItem->polygon();
    QPointF p1 = endPolygon.first() + myEndItem->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i) {
    p2 = endPolygon.at(i) + myEndItem->pos();
    polyLine = QLineF(p1, p2);
    QLineF::IntersectType intersectType =
        polyLine.intersect(centerLine, &intersectPoint);
    if (intersectType == QLineF::BoundedIntersection)
        break;
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, myStartItem->pos()));


    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

        QPointF PortLinkItemP1 = line().p1() + QPointF(sin(angle + Pi / 3) * PortLinkItemSize,
                                        cos(angle + Pi / 3) * PortLinkItemSize);
        QPointF PortLinkItemP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * PortLinkItemSize,
                                        cos(angle + Pi - Pi / 3) * PortLinkItemSize);

        PortLinkItemHead.clear();
        PortLinkItemHead << line().p1() << PortLinkItemP1 << PortLinkItemP2;

        painter->drawLine(line());
        painter->drawPolygon(PortLinkItemHead);
        if (isSelected()) {
            painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(centerLine);
    }*/
    painter->drawLine(line());
    if (isSelected()) {
        /*   painter->setPen(QPen(Qt::yellow, 1, Qt::DashLine));
            QLineF myLine = line();
            QLineF l1,l2;
            if(myLine.y1() != myLine.y2())
            {
                l1.setP1(QPointF(myLine.x1()-6,myLine.y1()));
                l1.setP2(QPointF(myLine.x2()-6,myLine.y2()));
                l2.setP1(QPointF(myLine.x1()+6,myLine.y1()));
                l2.setP2(QPointF(myLine.x2()+6,myLine.y2()));
            }
             else
            {
                l1.setP1(QPointF(myLine.x1(),myLine.y1()-6));
                l1.setP2(QPointF(myLine.x2(),myLine.y2()-6));
                l2.setP1(QPointF(myLine.x1(),myLine.y1()+6));
                l2.setP2(QPointF(myLine.x2(),myLine.y2()+6));
            }

           // myLine.translate(0, 4.0);
            painter->drawLine(l1);
            //myLine.translate(0,-8.0);
            painter->drawLine(l2);*/
           painter->setPen(QPen(Qt::blue, 4, Qt::SolidLine));
            painter->drawLine(line());
        }
}
