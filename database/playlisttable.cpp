#include "playlisttable.h"


namespace database {
//==============================================================================
PlayListTable::PlayListTable(DataBase* dataBase):Table(dataBase)
{

}
//------------------------------------------------------------------------------
PlayList PlayListTable::fromSqlQuery(QSharedPointer<QSqlQuery> query)
{

}
//------------------------------------------------------------------------------
QString PlayListTable::getTableCreateQueryText()
{
    QString QueryText = QStringLiteral("CREATE TABLE playlist(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                       "name TEXT UNIQUE,"
                                       "comment TEXT"
                                       ")");
    return QueryText;
}
//==============================================================================
}
