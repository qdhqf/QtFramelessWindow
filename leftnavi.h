#ifndef LEFTNAVI_H
#define LEFTNAVI_H
#include <QtWidgets>

#include "findtext.h"
#include "toolbutton.h"

class LocationView;
class LocationModel;
class QSqlDatabase;

class LeftNavi : public QFrame
{
    Q_OBJECT

public:
    explicit LeftNavi(QFrame *parent = 0);
    ~LeftNavi();
    void setDatabase(QSqlDatabase db);
private:
     QToolBar *naviToolBar;
     void     fillToolBar();
     QAction *actSer;
     FindTextContent *find;
     LocationView *siteTree;
     QTreeView *netTree;
     ToolButton *netHead;
     QSplitter *vSplit;
     QByteArray vSplitState;
     LocationModel *mode;
private slots:
     void slotShowFind();
     void showNetTree();
};



#endif // LEFTNAVI_H
