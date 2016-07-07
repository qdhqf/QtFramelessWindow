#include "nettopoview.h"
#include <QKeyEvent>
#include <QMenu>

NetTopoView::NetTopoView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void NetTopoView::keyPressEvent(QKeyEvent *event)
{
   qDebug("*********NetTopoView::keyPressEvent***************");
    switch (event->key())
    {
    case Qt::Key_Left :
        scale(1.2, 1.2);
        break;
    case Qt::Key_Right :
        scale(1 / 1.2, 1 / 1.2);
        break;
    case Qt::Key_Up :
        rotate(30);
        break;
    }
    QGraphicsView::keyPressEvent(event);
}

void NetTopoView::mousePressEvent(QMouseEvent *event)
{
    qDebug("************NetTopoView::mousePressEvent*****************");
    QGraphicsView::mousePressEvent(event);
}

void NetTopoView::paintEvent(QPaintEvent *event)
{
    qDebug("************NetTopoView::paintEvent*****************");
    QGraphicsView::paintEvent(event);
}

void NetTopoView::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug("************NetTopoView::mouseMoveEvent*****************");
    QGraphicsView::mouseMoveEvent(event);
}

void NetTopoView::contextMenuEvent(QContextMenuEvent *event)
{
    /*QMenu menu;
    QAction *moveAction = menu.addAction(QStringLiteral("添加网元"));
    QAction *actAction = menu.addAction(QStringLiteral("添加连接"));*/
    QGraphicsView::contextMenuEvent(event);
}



