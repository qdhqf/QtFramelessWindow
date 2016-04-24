#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QLayout>
#include "database.h"
#include <QtSql>


class HeaderBar;
class StatusBar;



class MainWindow : public QFrame
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

public slots:
    void showMenu(QPoint pt);

private:
    HeaderBar       *ptrHeaderBar;
    StatusBar        *ptrStatusBar;
    QVBoxLayout     *ptrMainLayout;
    DataLayer        db;
};



#endif // MAINWINDOW_H

