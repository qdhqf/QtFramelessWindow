/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "treeitem.h"
#include "treemodel.h"
#include <QtSql>

//!
TreeModel::TreeModel(const QStringList &headers, const QString tablename, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header ;

    rootItem = new TreeItem(rootData,"0");
    setupModelData(tablename, rootItem);
}
//! [0]

//! [1]
TreeModel::~TreeModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
 /*   if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();*/
}
//! [2]

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
 /*
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);

    return item->data(index.column());
 */
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    //判断显示的对象是checkbox，并且位于第一列
    if (role==Qt::CheckStateRole && index.column()==0)
        return static_cast<int>( item->isChecked() ? Qt::Checked : Qt::Unchecked );

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());
}

QString TreeModel::getItemId(const QModelIndex &index) const
{
    if (!index.isValid())
        return "NULL";
    TreeItem *item = getItem(index);
    return item->SelfId();

}

//! [3]
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
/*
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
*/
    if (!index.isValid())
        return 0;

    if (index.column()==0)   //如果是第一列的结点，则使其有显示checkbox的能力
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
//! [3]

//! [4]
TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
//! [4]

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{

    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}


bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
//! [8]

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
/*
   if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
  */
    if (role==Qt::CheckStateRole && index.column()==0)
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (value==Qt::Unchecked)
        {
            //m_checkedList.removeOne(index);
            item->setCheckState(false);
            emit(dataChanged(index, index));
        }
        else if(value==Qt::Checked)
        {
            //m_checkedList.append(index);
            item->setCheckState(true);
            emit(dataChanged(index, index));
        }
        int childCount = rowCount(index);
        if (childCount > 0)
        {
            //判断是否有子节点
            for (int i=0; i<childCount; i++)
            {
                //获得子节点的index
                QModelIndex child = this->index(i, 0, index);
                //递归，改变子节点的checkbox状态
                setData(child, value, Qt::CheckStateRole);
            }
        }
    }
    return true;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

// todo：use database source to replace this part, 用数据库记录代替lines
void TreeModel::setupModelData(const QString tablename, TreeItem *parent)
{
    QList<TreeItem*> parents; //like a stack,push the latest item into when find new child, popup the top item when children lookup finished
    QList<int> depths; //we have to change it to level
    parents << parent;
    depths << 0;
    int depth = 0;


    QString sql = "WITH RECURSIVE P (selfId, name, type, parentId, PATH, DEPTH)  AS (SELECT selfId, name, type, parentId, name||'/' AS PATH, 0 AS DEPTH FROM ";
            sql += tablename;
            sql += "  WHERE parentId = 0 UNION ALL ";
            sql += " SELECT  C.selfId, C.name, C.type, C.parentId, P.PATH||C.name||'/',  P.DEPTH + 1 AS DEPTH FROM ";
            sql += tablename;
            sql += " C JOIN P ON C.parentId = P.selfId) ";
            sql += " SELECT selfId , name, type, parentId, PATH, DEPTH FROM P ORDER BY PATH ASC;";
    QSqlQuery query;
    qDebug() << sql;
    query.exec(sql);
    while (query.next()) {
        qDebug() << query.value(0).toInt() << ", " << query.value(1).toString() << ", " << query.value(2).toInt() << ", " << query.value(3).toInt() << ", " << query.value(4).toString() << ", " << query.value(5).toInt();
        depth = query.value(5).toInt();

        QVector<QVariant> columnData;
        columnData << query.value(1).toString() << query.value(2).toInt() << query.value(0).toInt();
        if(depth > depths.last()){
           qDebug() << depth << "depths.last():" << depths.last();
           if (parents.last()->childCount() > 0) {
               qDebug() << "run in new parent";
               parents << parents.last()->child(parents.last()->childCount()-1);
               depths << depth;
           }
        }else {
            qDebug() << depth << "less";
            while (depth < depths.last() && parents.count() > 0) {
                parents.pop_back();
                depths.pop_back();
            }
         }
         TreeItem *parent = parents.last();
         if(parent == NULL)
         qDebug() << "FAILED";
         parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
         for (int column = 0; column < columnData.size(); ++column)
             parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
         parent->child(parent->childCount() - 1)->SetId(query.value(0).toString());

 }
}

void TreeModel::setCheckedStrList(TreeItem *item, QStringList &checkedStrList)
{
    if (item->isChecked())
    {
        checkedStrList.append(item->data(0).toString());
    }

    int childCount = item->childCount();
    if (childCount > 0)
    {
        // 判断是否有子节点
        for (int i=0; i<childCount; i++)
        {
            TreeItem *child = item->child(i);
            // 递归调用setCheckedStrList;
            setCheckedStrList(child, checkedStrList);
        }
    }
}

void TreeModel::getCheckedItemData(QString& resStr)
{
    QStringList checkedStrList;
    setCheckedStrList(rootItem, checkedStrList);

    for (int i=0; i<checkedStrList.size(); i++)
    {
        resStr += checkedStrList[i] + QString("\n");
    }
}
