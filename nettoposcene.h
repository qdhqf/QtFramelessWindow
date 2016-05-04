#ifndef NetTopoScene_H
#define NetTopoScene_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>

class NetTopoScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit NetTopoScene(QObject *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
signals:

public slots:

};

#endif // NetTopoScene_H
