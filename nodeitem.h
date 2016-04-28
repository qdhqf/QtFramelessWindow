#ifndef NODEITEM_H
#define NODEITEM_H

#include <QtWidgets>

class NodeItem : public QGraphicsPixmapItem
{
public:
    NodeItem();
    void setMyText(QString &text);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    void setColor(const QColor &color) { brushColor = color; }

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent (QGraphicsSceneHoverEvent * event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    QColor brushColor;
    QString nodeText;
};



#endif // NODEITEM_H
