#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class DataLayer
{
public:
    QSqlError initdbcon();

private:
    QSqlDatabase selfdb;
};


#endif // DATABASE_H
