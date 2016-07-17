#include "locationview.h"

//#include "mainapplication.h"
#include "locationmodel.h"
//#include "delegatewithoutfocus.h"

#include <QSqlTableModel>
#include <QSqlQuery>

// ----------------------------------------------------------------------------
LocationView::LocationView(QWidget * parent)
  : QTreeView(parent)
  , selectIdEn_(true)
  , autocollapseFolder_(false)
  , sourceModel_(0)
  , dragPos_(QPoint())
  , dragStartPos_(QPoint())
  , expandedOldId_(-1)
{
  setObjectName("LocationView_");
  setFrameStyle(QFrame::NoFrame);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setEditTriggers(QAbstractItemView::NoEditTriggers);

  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setUniformRowHeights(true);

  header()->setStretchLastSection(false);
  header()->setVisible(false);

/*  DelegateWithoutFocus *itemDelegate = new DelegateWithoutFocus(this);
  setItemDelegate(itemDelegate);*/

  setContextMenuPolicy(Qt::CustomContextMenu);

  setDragDropMode(QAbstractItemView::InternalMove);
  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);

  connect(this, SIGNAL(expanded(QModelIndex)), SLOT(slotExpanded(QModelIndex)));
  connect(this, SIGNAL(collapsed(QModelIndex)), SLOT(slotCollapsed(QModelIndex)));
}

void LocationView::setSourceModel(LocationModel *sourceModel)
{
  sourceModel_ = sourceModel;

  QSqlQuery q;
  q.exec("SELECT id FROM feeds WHERE f_Expanded=1 AND (xmlUrl='' OR xmlUrl IS NULL)");
  while (q.next()) {
    int feedId = q.value(0).toInt();
    expandedList.append(feedId);
  }
}

void LocationView::refresh()
{
  sourceModel_->refresh();
//  ((SiteProxyModel*)model())->reset();
  restoreExpanded();
}

void LocationView::setColumnHidden(const QString& column, bool hide)
{
  QTreeView::setColumnHidden(columnIndex(column),hide);
}

int LocationView::columnIndex(const QString& fieldName) const
{
  return sourceModel_->indexColumnOf(fieldName);
}


void LocationView::restoreExpanded()
{
 /* foreach (int id, expandedList) {
    //QModelIndex index = ((SiteProxyModel*)model())->mapFromSource(id);
    if (!isExpanded(index))
      setExpanded(index, true);
  }*/
}

/** @brief Process item expanding
 *----------------------------------------------------------------------------*/
void LocationView::slotExpanded(const QModelIndex &index)
{
  /*int feedId = sourceModel_->idByIndex(((SiteProxyModel*)model())->mapToSource(index));
  if (!expandedList.contains(feedId)) {
    expandedList.append(feedId);
    mainApp->sqlQueryExec(QString("UPDATE feeds SET f_Expanded=1 WHERE id=='%1'").arg(feedId));
  }

  if (!autocollapseFolder_ || (feedId == expandedOldId_))
    return;

  QModelIndex indexCollapsed = ((SiteProxyModel*)model())->mapFromSource(expandedOldId_);
  expandedOldId_ = feedId;

  if (index.parent() != indexCollapsed)
    collapse(indexCollapsed);

  int value = index.row();
  QModelIndex parent = index.parent();
  if (parent.isValid()) value = value + 1;
  while (parent.isValid()) {
    value = value + parent.row();
    parent = parent.parent();
  }
  verticalScrollBar()->setValue(value);  */
}

/** @brief Process item collapsing
 *----------------------------------------------------------------------------*/
void LocationView::slotCollapsed(const QModelIndex &index)
{
 /* int feedId = sourceModel_->idByIndex(((SiteProxyModel*)model())->mapToSource(index));
  expandedList.removeOne(feedId);
  mainApp->sqlQueryExec(QString("UPDATE feeds SET f_Expanded=0 WHERE id=='%1'").arg(feedId));*/
}

void LocationView::expandAll()
{
/*  expandedList.clear();
  QTreeView::expandAll();


  QSqlQuery q;
  q.exec("SELECT id FROM feeds WHERE (xmlUrl='' OR xmlUrl IS NULL)");
  while (q.next()) {
    int feedId = q.value(0).toInt();
    expandedList.append(feedId);
  }
  mainApp->sqlQueryExec("UPDATE feeds SET f_Expanded=1 WHERE (xmlUrl='' OR xmlUrl IS NULL)");*/
}

void LocationView::collapseAll()
{
 /* expandedList.clear();
  QTreeView::collapseAll();

  mainApp->sqlQueryExec("UPDATE feeds SET f_Expanded=0 WHERE (xmlUrl='' OR xmlUrl IS NULL)");*/
}





QModelIndex LocationView::indexPrevious(const QModelIndex &indexCur, bool isParent)
{
  QModelIndex index = QModelIndex();

  for(int i = indexCur.row()-1; i >= 0; --i) {
    index = model()->index(i, columnIndex("text"), indexCur.parent());
    if (index.isValid())
      return index;
  }

  index = indexCur.parent();
  if (index.isValid())
    return indexPrevious(index, true);

  return QModelIndex();
}


QModelIndex LocationView::indexNext(const QModelIndex &indexCur, bool isParent)
{
  QModelIndex index = QModelIndex();


  int rowCount = model()->rowCount(indexCur.parent());

  for(int i = indexCur.row()+1; i < rowCount; i++) {
    index = model()->index(i, columnIndex("text"), indexCur.parent());

    if (index.isValid())
      return index;
  }

  index = indexCur.parent();
  if (index.isValid())
    return indexNext(index, true);

  return QModelIndex();
}


void LocationView::mousePressEvent(QMouseEvent *event)
{

}

// ----------------------------------------------------------------------------
void LocationView::mouseReleaseEvent(QMouseEvent *event)
{
  dragStartPos_ = QPoint();
  QTreeView::mouseReleaseEvent(event);
}

// ----------------------------------------------------------------------------
void LocationView::mouseMoveEvent(QMouseEvent *event)
{
  if (dragStartPos_.isNull()) return;

  if ((event->pos() - dragStartPos_).manhattanLength() < qApp->startDragDistance())
    return;

  event->accept();

  dragPos_ = event->pos();

  QMimeData *mimeData = new QMimeData;
//  mimeData->setText("MovingItem");

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setHotSpot(event->pos() + QPoint(10,10));

  drag->exec();
}

// ----------------------------------------------------------------------------
void LocationView::mouseDoubleClickEvent(QMouseEvent *event)
{
  QModelIndex index = indexAt(event->pos());
  QRect rectText = visualRect(index);

  if (!index.isValid()) return;
  if (!(event->pos().x() >= rectText.x())) {
    QTreeView::mouseDoubleClickEvent(event);
    return;
  }

  if (indexClicked_ == indexAt(event->pos()))
    emit signalDoubleClicked();
  else
    mousePressEvent(event);
}

// ----------------------------------------------------------------------------
void LocationView::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Up)         emit pressKeyUp();
  else if (event->key() == Qt::Key_Down)  emit pressKeyDown();
  else if (event->key() == Qt::Key_Home)  emit pressKeyHome();
  else if (event->key() == Qt::Key_End)   emit pressKeyEnd();
}

// ----------------------------------------------------------------------------
void LocationView::currentChanged(const QModelIndex &current,
                                           const QModelIndex &previous)
{
/*  if (selectIdEn_) {
    QModelIndex index = ((SiteProxyModel*)model())->mapToSource(current);
    selectId_ = sourceModel_->idByIndex(index);
  }
  selectIdEn_ = true;

  QTreeView::currentChanged(current, previous);*/
}

// ----------------------------------------------------------------------------
void LocationView::dragEnterEvent(QDragEnterEvent *event)
{
  event->accept();
  dragPos_ = event->pos();
  viewport()->update();
}

// ----------------------------------------------------------------------------
void LocationView::dragLeaveEvent(QDragLeaveEvent *event)
{
  event->accept();
  dragPos_ = QPoint();
  viewport()->update();
}

// ----------------------------------------------------------------------------
void LocationView::dragMoveEvent(QDragMoveEvent *event)
{
  if (dragPos_.isNull()) {
    event->ignore();
    viewport()->update();
    return;
  }

  dragPos_ = event->pos();
  QModelIndex dragIndex = indexAt(dragPos_);


    if ((dragIndex.row() == currentIndex().row()) &&
        (dragIndex.parent() == currentIndex().parent()))
      event->ignore();  // don't move feed to itseelf
    else if (dragIndex.parent() == currentIndex())
      event->ignore();  // don't move feed to same parent
    else {
      bool ignore = false;
      QModelIndex child = dragIndex.parent();
      while (child.isValid()) {
        if ((child.row() == currentIndex().row()) &&
            (child.parent() == currentIndex().parent())) {
          event->ignore();  // don't move feed inside itself
          ignore = true;
          break;
        }
        child = child.parent();
      }
      if (!ignore) event->accept();
    }


  viewport()->update();

  if (shouldAutoScroll(event->pos()))
    startAutoScroll();
}

// ----------------------------------------------------------------------------
bool LocationView::shouldAutoScroll(const QPoint &pos) const
{
    if (!hasAutoScroll())
        return false;
    QRect area = viewport()->rect();
    return (pos.y() - area.top() < autoScrollMargin())
        || (area.bottom() - pos.y() < autoScrollMargin())
        || (pos.x() - area.left() < autoScrollMargin())
        || (area.right() - pos.x() < autoScrollMargin());
}

// ----------------------------------------------------------------------------
void LocationView::dropEvent(QDropEvent *event)
{
  dragPos_ = QPoint();
  viewport()->update();

  event->setDropAction(Qt::MoveAction);
  event->accept();
  handleDrop(event);
}

// ----------------------------------------------------------------------------
void LocationView::paintEvent(QPaintEvent *event)
{
  QTreeView::paintEvent(event);
}

// ----------------------------------------------------------------------------
QPersistentModelIndex LocationView::selectIndex()
{
  return sourceModel_->indexById(selectId_);
}


void LocationView::updateCurrentIndex(const QModelIndex &index)
{
  setUpdatesEnabled(false);
  int topRow = verticalScrollBar()->value();
  setCurrentIndex(index);
  verticalScrollBar()->setValue(topRow);
  setUpdatesEnabled(true);
}

// ----------------------------------------------------------------------------
void LocationView::handleDrop(QDropEvent *e)
{

}
