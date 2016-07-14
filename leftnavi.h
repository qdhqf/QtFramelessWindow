#ifndef LEFTNAVI_H
#define LEFTNAVI_H
#include <QtWidgets>

#include "findtext.h"
#include "toolbutton.h"

class SiteView;
class SiteModel;
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
     SiteView *siteTree;
     QTreeView *netTree;
     ToolButton *netHead;
     QSplitter *vSplit;
     QByteArray vSplitState;
     SiteModel *mode;
private slots:
     void slotShowFind();
     void showNetTree();
};



#endif // LEFTNAVI_H
