#ifndef LEFTNAVI_H
#define LEFTNAVI_H
#include <QtWidgets>

#include "findtext.h"
#include "toolbutton.h"

class SiteView;

class LeftNavi : public QFrame
{
    Q_OBJECT

public:
    explicit LeftNavi(QFrame *parent = 0);
    ~LeftNavi();
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
private slots:
     void slotShowFind();
     void showNetTree();
};



#endif // LEFTNAVI_H
