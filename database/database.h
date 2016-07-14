#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore>
#include <QtSql>

class DataLayer :public QObject
{
  Q_OBJECT
public:
    QSqlError initdbcon();
    QSqlDatabase db();
    void closedbcon();
private:
    QSqlDatabase selfdb;
};


#endif // DATABASE_H
