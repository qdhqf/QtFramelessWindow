#ifndef LEFTNAVI_H
#define LEFTNAVI_H
#include <QtWidgets>

#include "findtext.h"
#include "toolbutton.h"

class TreeModel;
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
     QAction *actSearch;
     FindTextContent *find;
     QTreeView *placeTree;
     QTreeView *netTree;
     ToolButton *netHead;
     QSplitter *vSplit;
     QByteArray vSplitState;
     TreeModel *plcmodel;
     TreeModel *netmodel;
private slots:
     void slotShowFind();
     void showNetTree();
     void slotPlaceClicked(QModelIndex idx);
     void slotNetworkClicked(QModelIndex idx);
};



#endif // LEFTNAVI_H
