#include "leftnavi.h"
#include "siteview.h"

LeftNavi::LeftNavi(QFrame *parent) :
    QFrame(parent)
{
    naviToolBar = new QToolBar(this);
    naviToolBar->setObjectName("naviToolBar");
    naviToolBar->setStyleSheet(QString("#naviToolBar { border-bottom: 1px solid %1;}").
                               arg(qApp->palette().color(QPalette::Dark).name()));
    fillToolBar();

    find = new FindTextContent(this);
    find->hide();
///Begin Sites Tree View
    QLabel *siteHeadLabel = new QLabel(this);
    siteHeadLabel->setText("Sites");
    ToolButton *siteHead = new ToolButton(this);
    siteHead->setIcon(QIcon(":/image/naviBar/siteShow.png"));
    siteHead->setFocusPolicy(Qt::NoFocus);
    siteHead->setMaximumSize(16, 16);
    siteHead->setAutoRaise(true);
    QHBoxLayout *sitePanelLayout = new QHBoxLayout();
    sitePanelLayout->setMargin(1);
    sitePanelLayout->addSpacing(2);
    sitePanelLayout->addWidget(siteHeadLabel, 1);
    sitePanelLayout->addWidget(siteHead);
    QWidget *sitePanel = new QWidget(this);
    sitePanel->setObjectName("sitePanel");
    sitePanel->setLayout(sitePanelLayout);
    sitePanel->setStyleSheet(QString("#sitePanel { border-bottom: 1px solid %1;}").
                                   arg(qApp->palette().color(QPalette::Dark).name()));
    siteTree = new SiteView(this);
    siteTree->setObjectName("siteTree");

    QVBoxLayout *siteLayout = new QVBoxLayout();
    siteLayout->setMargin(0);
    siteLayout->setSpacing(0);
    siteLayout->addWidget(sitePanel);
    siteLayout->addWidget(siteTree, 1);
    QWidget *siteWidget = new QWidget(this);
    siteWidget->setLayout(siteLayout);
//End Site Tree

///Begin Network Tree
    QLabel *netHeadLabel = new QLabel(this);
    netHeadLabel->setText("Networks");
    netHead = new ToolButton(this);
    netHead->setIcon(QIcon(":/image/naviBar/netShow.png"));
    netHead->setFocusPolicy(Qt::NoFocus);
    netHead->setMaximumSize(16, 16);
    netHead->setAutoRaise(true);
    QHBoxLayout *netPanelLayout = new QHBoxLayout();
    netPanelLayout->setMargin(1);
    netPanelLayout->addSpacing(2);
    netPanelLayout->addWidget(netHeadLabel, 1);
    netPanelLayout->addWidget(netHead);
    QWidget *netPanel = new QWidget(this);
    netPanel->setObjectName("netPanel");
    netPanel->setLayout(netPanelLayout);
    netPanel->setStyleSheet(QString("#netPanel { border-bottom: 1px solid %1;}").
                                   arg(qApp->palette().color(QPalette::Dark).name()));
    netTree =  new QTreeView(this);
    netTree->setObjectName("netTree");
    netTree->setStyleSheet("#netTree { border: none; padding: 0px;}");
    QVBoxLayout *netLayout = new QVBoxLayout();
    netLayout->setMargin(0);
    netLayout->setSpacing(0);
    netLayout->addWidget(netPanel);
    netLayout->addWidget(netTree, 1);
    QWidget *netWidget = new QWidget(this);
    netWidget->setLayout(netLayout);
//End Network Tree
    siteWidget->setStyleSheet("QWidget { border: none; padding: 0px;}");
    vSplit = new QSplitter(Qt::Vertical);
    vSplit->setFrameStyle(QFrame::NoFrame);
    vSplit->setChildrenCollapsible(false);
    vSplit->setHandleWidth(1);

    vSplit->setStyleSheet(
            QString("QSplitter::handle {background: qlineargradient("
                    "x1: 0, y1: 0, x2: 0, y2: 1,"
                    "stop: 0 %1, stop: 0.07 %2);}").
            arg(qApp->palette().background().color().name()).
            arg(qApp->palette().color(QPalette::Dark).name()));
    vSplit->addWidget(siteWidget);
    vSplit->addWidget(netWidget);

    QVBoxLayout *navilay = new QVBoxLayout(this);
    navilay->setMargin(0);
    navilay->setSpacing(0);
    navilay->addWidget(naviToolBar);
    navilay->addWidget(find);
    navilay->addWidget(vSplit);
    setLayout(navilay);

    connect(netHead, SIGNAL(clicked()),
            this, SLOT(showNetTree()));
/*    connect(vSplit, SIGNAL(splitterMoved(int,int)),
            this, SLOT(vSplitMoved(int,int)));*/

    netHeadLabel->installEventFilter(this);
    netTree->installEventFilter(this);



}


LeftNavi::~LeftNavi()
{

}

void LeftNavi::fillToolBar()
{
    QAction *actAdd = new QAction(this);
    actAdd->setText("Add");
    actAdd->setIcon(QIcon(":/image/naviBar/add.png"));
    naviToolBar->addAction(actAdd);
    naviToolBar->addSeparator();

    QAction *actFil = new QAction(this);
    actFil->setText("Filter");
    actFil->setIcon(QIcon(":/image/naviBar/filter.png"));
    naviToolBar->addAction(actFil);
    naviToolBar->addSeparator();

    QAction *actUpd = new QAction(this);
    actUpd->setText("Update");
    actUpd->setIcon(QIcon(":/image/naviBar/update.png"));
    naviToolBar->addAction(actUpd);
    naviToolBar->addSeparator();

    actSer = new QAction(this);
    actSer->setText("Search");
    actSer->setIcon(QIcon(":/image/naviBar/find.png"));
    naviToolBar->addAction(actSer);
    actSer->setCheckable(true);
    actSer->setChecked(false);

    connect(actSer,SIGNAL(triggered()),this,SLOT(slotShowFind()));
}

void LeftNavi::slotShowFind()
{
    actSer->isChecked()?find->show():find->hide();
    //actSer->setChecked(!actSer->isChecked());
}


void LeftNavi::showNetTree()
{
  if (netTree->isHidden()) {
    netHead->setIcon(QIcon(":/image/naviBar/netHide.png"));
    netHead->setToolTip(tr("Hide Network"));
    netTree->show();
    vSplit->restoreState(vSplitState);
  } else {
    vSplitState = vSplit->saveState();
    netHead->setIcon(QIcon(":/image/naviBar/netShow.png"));
    netHead->setToolTip(tr("Show Network"));
    netTree->hide();
    QList <int> sizes;
    sizes << height() << 20;
    vSplit->setSizes(sizes);
  }
}
