#include "nettoposcene.h"
#include <QMenu>


NetTopoScene::NetTopoScene(QObject *parent) :
    QGraphicsScene(parent)
{
    //clearFocus();
}

void NetTopoScene::keyPressEvent(QKeyEvent *event)
{
    qDebug("*********NetTopoScene::keyPressEvent***************");
    return QGraphicsScene::keyPressEvent(event);
}

void NetTopoScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("*********NetTopoScene::mousePressEvent***************");
    QGraphicsScene::mousePressEvent(event);
}

void NetTopoScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("*********NetTopoScene::mouseMoveEvent***************");
    QGraphicsScene::mouseMoveEvent(event);
}

void NetTopoScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
   /* QMenu menu;
    QAction *moveAction = menu.addAction(QStringLiteral("添加网元"));
    QAction *actAction = menu.addAction(QStringLiteral("添加连接"));*/
    QGraphicsScene::contextMenuEvent(event);
}

void NetTopoScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("*********NetTopoScene::mouseReleaseEvent***************");
    QGraphicsScene::mouseReleaseEvent(event);
}
