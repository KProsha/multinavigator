#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QSqlQuery>
#include <QList>
#include <QSharedPointer>
#include <QDebug>
#include <QSqlError>

namespace database {
//==============================================================================
class DataBase;

class Table
{

public:
    Table(DataBase* dB);
    virtual ~Table(){}

    void createTable();
protected:
    DataBase* dataBase;

    virtual QString getTableCreateQueryText() = 0;

    QSharedPointer<QSqlQuery> sendQuery(const QString& queryText);
};

//==============================================================================
}

#endif // TABLE_H
