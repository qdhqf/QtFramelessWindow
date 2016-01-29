#include "contentwidget.h"

ContentWidget::ContentWidget(QWidget *parent):
    QWidget(parent)
{
     setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     setAutoFillBackground(true);
     QPalette pal;
     QPixmap pix(":/image/frame.jpg");
     pal.setBrush(backgroundRole(),QBrush(pix));
     setPalette(pal);

     //this block doesn't work, can't figure it out why.
     QTreeWidget tree;
     QTableWidget table;
     tree.setMinimumWidth(50);
     table.setMinimumWidth(100);
     mainSplitter.setParent(this);
     mainSplitter.addWidget(&tree);
     mainSplitter.addWidget(&table);


}

ContentWidget::~ContentWidget()
{

}

