#include "fileplaylisttable.h"


namespace database {
//==============================================================================
FilePlayListTable::FilePlayListTable(DataBase* dataBase):Table(dataBase)
{

}
//------------------------------------------------------------------------------
FilePlayList FilePlayListTable::fromSqlQuery(QSharedPointer<QSqlQuery> query)
{

}
//------------------------------------------------------------------------------
QString FilePlayListTable::getTableCreateQueryText()
{
    QString QueryText = QStringLiteral("CREATE TABLE fileplaylist(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                       "fileId INTEGER,"
                                       "playListId INTEGER"
                                       ")");

    return QueryText;
}

//==============================================================================
}
