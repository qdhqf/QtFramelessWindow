#ifndef TreeView_H
#define TreeView_H


#include <QtWidgets>

class TreeView : public QTreeView
{
  Q_OBJECT
public:
  TreeView(QWidget * parent = 0);

signals:
  void signalSetItemRead(QModelIndex index, int read);
  void signalSetItemStar(QModelIndex index, int starred);
  void signalDoubleClicked(QModelIndex index);
  void signalMiddleClicked(QModelIndex index);
  void signaNewslLabelClicked(QModelIndex index);
  void pressKeyUp(const QModelIndex &index);
  void pressKeyDown(const QModelIndex &index);
  void pressKeyHome(const QModelIndex &index);
  void pressKeyEnd(const QModelIndex &index);
  void pressKeyPageUp(const QModelIndex &index);
  void pressKeyPageDown(const QModelIndex &index);

protected:
  virtual void mousePressEvent(QMouseEvent*);
  virtual void mouseMoveEvent(QMouseEvent*);
  virtual void mouseDoubleClickEvent(QMouseEvent*);
  virtual void keyPressEvent(QKeyEvent*);

private:
  QModelIndex indexClicked_;

};

#endif // TreeView_H
