#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include "database.h"
//#include <QtSql>


class HeaderBar;
class StatusBar;
class LeftNavi;



class MainWindow : public QFrame
{
    Q_OBJECT

public:
    explicit MainWindow(QFrame *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void changeEvent(QEvent *e);

public slots:
    void showMenu(QPoint pt);
    void showMaxRestore();

private:
    void createToolBarNull();
    void createActions();
private:
    HeaderBar       *ptrHeaderBar;
    StatusBar       *ptrStatusBar;
  //  QVBoxLayout     *ptrCentreLayout;
   // QHBoxLayout     *ptrMainViewLayout;
    QPushButton     *pushButtonNull_;
    LeftNavi        *lft;
    bool             isLeftNaviVisuable;
    DataLayer        db;
private slots:
    void slotVisibledLeftWiew();
};



#endif // MAINWINDOW_H

