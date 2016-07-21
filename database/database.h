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
    bool CreateTables();
    void closedbcon();
private:
    QSqlDatabase selfdb;
    bool createplacetable();
    bool createnettable();
    bool dbFileExists_;
};


#endif // DATABASE_H
