#ifndef SITEVIEW_H
#define SITEVIEW_H


#include <QtWidgets>
#include <sitemodel.h>

class SiteView : public QTreeView
{
  Q_OBJECT
public:
  explicit SiteView(QWidget * parent = 0);
  int selectId_;
  bool selectIdEn_;
  bool autocollapseFolder_;

  void setSourceModel(SiteModel *sourceModel);
  void refresh();
  void setColumnHidden(const QString& column, bool hide);
  int columnIndex(const QString& fieldName) const;


  QModelIndex indexPrevious(const QModelIndex &indexCur, bool isParent = false);
  QModelIndex indexNext(const QModelIndex &indexCur, bool isParent = false);


public slots:
  void restoreExpanded();
  void expandAll();
  void collapseAll();
  QPersistentModelIndex selectIndex();
  void updateCurrentIndex(const QModelIndex &index);

signals:
  void signalDoubleClicked();
  void signalMiddleClicked();
  void pressKeyUp();
  void pressKeyDown();
  void pressKeyHome();
  void pressKeyEnd();
  void signalDropped(const QModelIndex &where, int how);

protected:
  virtual void mousePressEvent(QMouseEvent*);
  virtual void mouseReleaseEvent(QMouseEvent*event);
  virtual void mouseMoveEvent(QMouseEvent*);
  virtual void mouseDoubleClickEvent(QMouseEvent*);
  virtual void keyPressEvent(QKeyEvent*);
  virtual void currentChanged(const QModelIndex &current,
                              const QModelIndex &previous);
  void dragEnterEvent(QDragEnterEvent *event);
  void dragLeaveEvent(QDragLeaveEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
  void dropEvent(QDropEvent *event);
  void paintEvent(QPaintEvent *event);

private slots:
  void slotExpanded(const QModelIndex&index);
  void slotCollapsed(const QModelIndex&index);

private:
  SiteModel *sourceModel_;
  QPoint dragPos_;
  QPoint dragStartPos_;
  QList<int> expandedList;
  int expandedOldId_;
  QModelIndex indexClicked_;

  void handleDrop(QDropEvent *e);
  bool shouldAutoScroll(const QPoint &pos) const;

};

#endif // SITEVIEW_H
