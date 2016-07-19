#include "database.h"

QSqlError DataLayer::initdbcon()
{
    qDebug() << QSqlDatabase::drivers();

    selfdb = QSqlDatabase::addDatabase("QSQLITE");
    selfdb.setDatabaseName("transdb.db3");

    /*
    selfdb = QSqlDatabase::addDatabase("SQLITECIPHER");
    selfdb.setPassword("12345");
    if (QFile("transdb.db").exists()) {
      dbFileExists_ = true;
    }
    if(dbFileExists_)
     {
        selfdb.setConnectOptions("OPEN_WITH_KEY");
        qDebug() << "dbFileExists_ is true";
     }
      else
         {
             selfdb.setConnectOptions("QSQLITE_CREATE_KEY");// only for first time usage
             qDebug() << "dbFileExists_ is false";
         }
*/
    if(!selfdb.open()){
        qDebug() << "Can not open connection.";
        //exit(CONNECTION_FAILED);
        return selfdb.lastError();
    }

    CreateTables();


 /*   query.exec("select id, name from mapping");
    while (query.next()) {
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString();
    }*/
    return QSqlError();
}

void DataLayer::closedbcon()
{
    selfdb.close();
}

QSqlDatabase  DataLayer::db()
{
    return selfdb;
}

bool DataLayer::CreateTables()
{
    if(!createlocationtable()) return false;
    return true;
}

bool DataLayer::createlocationtable()
{
    QSqlQuery query;
    query.exec("	CREATE TABLE location(selfId integer primary key, parentId integer, name varchar, type int,edgetype tinyint)");
    qDebug() << selfdb.databaseName() << selfdb.tables();
    if(QSqlError().isValid())
    {
        qDebug() << QSqlError();
        return false;
    }
    return true;
}

bool DataLayer::createnetworktable()
{
    return true;
}
