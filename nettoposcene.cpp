#include "nettoposcene.h"

NetTopoScene::NetTopoScene(QObject *parent) :
    QGraphicsScene(parent)
{
    clearFocus();
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
