#include "table.h"

#include "database.h"

#include <QSqlError>

namespace database {
//==============================================================================


Table::Table(DataBase* dB)
{
    dataBase = dB;
}
//------------------------------------------------------------------------------
void Table::createTable()
{
    sendQuery(getTableCreateQueryText());
}
//------------------------------------------------------------------------------
QSharedPointer<QSqlQuery> Table::sendQuery(const QString& queryText)
{
    return dataBase->sendQuery(queryText);
}

//==============================================================================
}


