#ifndef NODEITEM_H
#define NODEITEM_H

#include <QtWidgets>

class PortLinkItem;

class NodeItem : public QGraphicsPixmapItem
{
public:
    enum {Type = UserType + 1};
    NodeItem();
    void setMyText(QString &text);
    void addLink(PortLinkItem *link);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    void setColor(const QColor &color) { brushColor = color; }
    int type() const {return Type;}
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent (QGraphicsSceneHoverEvent * event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
private:
    QColor brushColor;
    QString nodeText;
    QList<PortLinkItem *> links;
};



#endif // NODEITEM_H
