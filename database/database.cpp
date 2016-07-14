#include "database.h"

QSqlError DataLayer::initdbcon()
{
    qDebug() << QSqlDatabase::drivers();
    selfdb.setDatabaseName("transdb.db");
    /*
    selfdb = QSqlDatabase::addDatabase("QSQLITE");
    */
    selfdb = QSqlDatabase::addDatabase("SQLITECIPHER");
    selfdb.setPassword("12345");
    selfdb.setConnectOptions("OPEN_WITH_KEY");
    //selfdb.setConnectOptions("QSQLITE_CREATE_KEY"); // only for first time usage

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
    query.exec("select id, name from mapping");
    while (query.next()) {
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString();
    }
    //query.exec("drop table mapping");
    //selfdb.close();


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
