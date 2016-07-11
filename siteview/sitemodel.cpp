#include "sitemodel.h"
#include "siteproxymodel.h"

#include <QtCore>
#include <QPainter>

SiteModel::SiteModel(QObject *parent)
  : QAbstractItemModel(parent)
  , defaultIconSite_(false)
  , view_(0)
  , rootParentId_(0)
{
  setObjectName("SiteModel");

  refresh();
}

SiteModel::~SiteModel()
{
  clear();
}

void SiteModel::clear()
{
  id2RowList_.clear();
  parid2RowList_.clear();
  columnsList_.clear();

  qDeleteAll(userDataList_);
  userDataList_.clear();
}

void SiteModel::refresh()
{

  beginResetModel();
  clear();
  endResetModel();


  queryModel_.setQuery("SELECT * FROM feeds ORDER BY parentId, rowToParent");
  while (queryModel_.canFetchMore())
    queryModel_.fetchMore();

  indexId_ = queryModel_.record().indexOf("id");
  indexParid_ = queryModel_.record().indexOf("parentId");
  for (int i = 0; i < queryModel_.record().count(); i++) {
    columnsList_[i] = i;
  }
  columnsList_[0] = queryModel_.record().indexOf("text");
  columnsList_[queryModel_.record().indexOf("text")] = 0;

  for (int i = 0; i < queryModel_.rowCount(); i++) {
    int id = queryModel_.record(i).value(indexId_).toInt();
    id2RowList_[id] = i;
    int parid = queryModel_.record(i).value(indexParid_).toInt();
    parid2RowList_[i] = parid;
    userDataList_[id] = new UserData(id, parid, queryModel_.record(i));
  }
}

UserData * SiteModel::userDataById(int id) const
{
  return userDataList_.value(id, 0);
}

int SiteModel::rowById(int id) const
{
  return id2RowList_.value(id, -1);
}

int SiteModel::rowByParid(int parid) const
{
  return parid2RowList_.key(parid, -1);
}

int SiteModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return parid2RowList_.keys(idByIndex(parent)).count();
  else
    return parid2RowList_.keys(rootParentId_).count();
}

int SiteModel::columnCount(const QModelIndex&) const
{
  return queryModel_.record().count();
}

QModelIndex SiteModel::index(int row, int column, const QModelIndex &parent) const
{
  if (row == -1)
    return QModelIndex();

  int id = 0;
  if (parent.isValid())
    id = id2RowList_.key(row + rowByParid(idByIndex(parent)), 0);
  else
    id = id2RowList_.key(row, 0);

  UserData *userData = userDataById(id);
  if (userData)
    return createIndex(row, column, userData);
  else
    return QModelIndex();
}

QModelIndex SiteModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
    return QModelIndex();

  int parid = paridByIndex(index);
  if (parid == rootParentId_)
    return QModelIndex();

  UserData *userData = userDataById(parid);
  if (userData) {
    int row = rowById(parid) - rowByParid(userData->parid);
    return createIndex(row, 0, userData);
  } else {
    return QModelIndex();
  }
}

QVariant SiteModel::data(const QModelIndex &index, int role) const
{
  if (role == Qt::FontRole) {
    QFont font = font_;
    if (indexColumnOf("text") == index.column()) {
      if (0 < indexSibling(index, "unread").data(Qt::EditRole).toInt())
        font.setBold(true);
    }
    return font;
  } else if (role == Qt::DisplayRole){
    if (indexColumnOf("unread") == index.column()) {
      int unread = indexSibling(index, "unread").data(Qt::EditRole).toInt();
      if (0 == unread) {
        return QVariant();
      } else {
        QString qStr = QString("(%1)").arg(unread);
        return qStr;
      }
    } else if (indexColumnOf("undeleteCount") == index.column()) {
      QString qStr = QString("(%1)").
          arg(indexSibling(index, "undeleteCount").data(Qt::EditRole).toInt());
      return qStr;
    } else if (indexColumnOf("updated") == index.column()) {
      QDateTime dtLocal;
      QString strDate = indexSibling(index, "updated").data(Qt::EditRole).toString();

      if (!strDate.isNull()) {
        QDateTime dtLocalTime = QDateTime::currentDateTime();
        QDateTime dtUTC = QDateTime(dtLocalTime.date(), dtLocalTime.time(), Qt::UTC);
        int nTimeShift = dtLocalTime.secsTo(dtUTC);

        QDateTime dt = QDateTime::fromString(strDate, Qt::ISODate);
        dtLocal = dt.addSecs(nTimeShift);

        QString strResult;
        if (QDateTime::currentDateTime().date() <= dtLocal.date())
          strResult = dtLocal.toString(formatTime_);
        else
          strResult = dtLocal.toString(formatDate_);
        return strResult;
      } else {
        return QVariant();
      }
    }
  } else if (role == Qt::TextColorRole) {
    if (indexColumnOf("unread") == index.column()) {
      return QColor(countNewsUnreadColor_);
    }

    QModelIndex currentIndex = ((SiteProxyModel*)view_->model())->mapToSource(view_->currentIndex());
    if ((index.row() == currentIndex.row()) && (index.parent() == currentIndex.parent()) &&
        view_->selectionModel()->selectedRows(0).count()) {
      return QColor(focusedFeedTextColor_);
    }

    if (indexColumnOf("text") == index.column()) {
      if (indexSibling(index, "newCount").data(Qt::EditRole).toInt() > 0) {
        return QColor(feedWithNewNewsColor_);
      }
    }

    if (indexColumnOf("text") == index.column()) {
      if (indexSibling(index, "disableUpdate").data(Qt::EditRole).toBool()) {
        return QColor(feedDisabledUpdateColor_);
      }
    }

    return QColor(textColor_);
  } else if (role == Qt::BackgroundRole) {
    QModelIndex currentIndex = ((SiteProxyModel*)view_->model())->mapToSource(view_->currentIndex());
    if ((index.row() == currentIndex.row()) && (index.parent() == currentIndex.parent()) &&
        view_->selectionModel()->selectedRows(0).count()) {
      if (!focusedFeedBGColor_.isEmpty())
        return QColor(focusedFeedBGColor_);
    }
  } else if (role == Qt::DecorationRole) {
    if (indexColumnOf("text") == index.column()) {
        if (!defaultIconSite_) {
          QByteArray byteArray = indexSibling(index, "image").data(Qt::EditRole).toByteArray();
          if (!byteArray.isNull()) {
            QImage resultImage;
            if (resultImage.loadFromData(QByteArray::fromBase64(byteArray))) {
              QString strStatus = indexSibling(index, "status").data(Qt::EditRole).toString();
              if (strStatus.section(" ", 0, 0).toInt() != 0) {
                QImage image;
                if (strStatus.section(" ", 0, 0).toInt() < 0)
                  image.load(":/images/bulletError");
                else if (strStatus.section(" ", 0, 0).toInt() == 1)
                  image.load(":/images/bulletUpdate");
                QPainter resultPainter(&resultImage);
                resultPainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
                resultPainter.drawImage(0, 0, image);
                resultPainter.end();
              }
              return resultImage;
            }
          }
        }
        QImage resultImage(":/images/feed");
        QString strStatus = indexSibling(index, "status").data(Qt::EditRole).toString();
        if (strStatus.section(" ", 0, 0).toInt() != 0) {
          QImage image;
          if (strStatus.section(" ", 0, 0).toInt() < 0)
            image.load(":/images/bulletError");
          else if (strStatus.section(" ", 0, 0).toInt() == 1)
            image.load(":/images/bulletUpdate");

          QPainter resultPainter(&resultImage);
          resultPainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
          resultPainter.drawImage(0, 0, image);
          resultPainter.end();
        }
        return resultImage;
    }
  } else if (role == Qt::TextAlignmentRole) {
    if (indexColumnOf("id") == index.column()) {
      int flag = Qt::AlignRight|Qt::AlignVCenter;
      return flag;
    }
  } else if (role == Qt::ToolTipRole) {
    if (indexColumnOf("text") == index.column()) {
      QString title = index.data(Qt::EditRole).toString();
      QRect rectText = view_->visualRect(index);
      int width = rectText.width() - 16 - 12;
      QFont font = font_;
      if (0 < indexSibling(index, "unread").data(Qt::EditRole).toInt())
        font.setBold(true);
      QFontMetrics fontMetrics(font);

      if (width < fontMetrics.width(title))
        return title;
    }
    return QString("");
  }

  if (!((role == Qt::EditRole) || (role == Qt::DisplayRole)))
    return QVariant();

  QSqlRecord record = static_cast<UserData*>(index.internalPointer())->record;
  return record.value(indexColumnOf(index.column()));
}

bool SiteModel::setData(const QModelIndex &index, const QVariant &value, int)
{
  if (!index.isValid())
    return false;

  QSqlRecord *record = &static_cast<UserData*>(index.internalPointer())->record;
  record->setValue(indexColumnOf(index.column()), value);
  return true;
}

Qt::ItemFlags SiteModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

  if (index.isValid())
    return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
  else
    return Qt::ItemIsDropEnabled | defaultFlags;
}

Qt::DropActions SiteModel::supportedDropActions() const
{
  return Qt::MoveAction;
}

QModelIndex SiteModel::indexById(int id) const
{
  QModelIndex parentIndex = QModelIndex();
  UserData *userData = userDataById(id);
  if (userData)
    parentIndex = indexById(userData->parid);
  for (int i = 0; i < rowCount(parentIndex); i++) {
    if (idByIndex(index(i, 0, parentIndex)) == id)
      return index(i,0,parentIndex);
  }
  return QModelIndex();
}

int SiteModel::idByIndex(const QModelIndex &index) const
{
  if (index.isValid())
    return static_cast<UserData*>(index.internalPointer())->id;
  return 0;
}

int SiteModel::paridByIndex(const QModelIndex &index) const
{
  if (index.isValid())
    return static_cast<UserData*>(index.internalPointer())->parid;
  return 0;
}

int SiteModel::indexColumnOf(int column) const
{
  return columnsList_.value(column, column);
}

int SiteModel::indexColumnOf(const QString &name) const
{
  return indexColumnOf(queryModel_.record().indexOf(name));
}

void SiteModel::setView(QTreeView *view)
{
  view_ = view;
}

QVariant SiteModel::dataField(const QModelIndex &index, const QString &fieldName) const
{
  return indexSibling(index, fieldName).data(Qt::EditRole);
}

QModelIndex SiteModel::indexSibling(const QModelIndex &index, const QString &fieldName) const
{
  return this->index(index.row(), indexColumnOf(fieldName), index.parent());
}
