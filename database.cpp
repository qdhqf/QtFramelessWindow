#include "database.h"

QSqlError DataLayer::initdbcon()
{
    selfdb = QSqlDatabase::addDatabase("QPSQL");
    selfdb.setHostName("localhost");
    selfdb.setDatabaseName("transdb");
    selfdb.setUserName("postgres");
    selfdb.setPassword("Cqupt1953");
    if(!selfdb.open()){
        return selfdb.lastError();
    }
    return QSqlError();
}
