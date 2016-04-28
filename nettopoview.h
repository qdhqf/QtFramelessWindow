#ifndef NetTopoView_H
#define NetTopoView_H

#include <QGraphicsView>

class NetTopoView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit NetTopoView(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
signals:

public slots:

};

#endif // NetTopoView_H
