#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>




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
    void slot_switchPage(int index);

private:
    void createToolBarNull();
    void createActions();
private:
    HeaderBar       *ptrHeaderBar;
    StatusBar       *ptrStatusBar;
    QPushButton     *pushButtonNull_;
    LeftNavi        *lft;
    QStackedWidget  *rgt;
    bool             isLeftNaviVisuable;

private slots:
    void slotVisibledLeftWiew();
};



#endif // MAINWINDOW_H

