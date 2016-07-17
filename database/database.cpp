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
    QSqlQuery query;
    query.exec("create table mapping (id int, name varchar)");
    query.exec("insert into mapping values (1, 'AAA')");
    query.exec("insert into mapping values (2, 'BBB')");
    query.exec("insert into mapping values (3, 'CCC')");
    query.exec("insert into mapping values (3, 'DDD')");
    query.exec("insert into mapping values (4, 'EEE')");
    query.exec("insert into mapping values (5, 'FFF')");
    query.exec("insert into mapping values (6, 'GGG')");
    qDebug() << selfdb.databaseName() << selfdb.tables();

    query.exec("select id, name from mapping");
    while (query.next()) {
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString();
    }
    //query.exec("drop table mapping");
    selfdb.close();


    return QSqlError();
}

void DataLayer::closedbcon()
{
    //selfdb.close();
}

QSqlDatabase  DataLayer::db()
{
    return selfdb;
}
