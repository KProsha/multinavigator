#ifndef FILEPLAYLISTTABLE_H
#define FILEPLAYLISTTABLE_H

#include "table.h"
#include "types/fileplaylist.h"

namespace database {
//==============================================================================
class FilePlayListTable: public Table
{
public:
    FilePlayListTable(DataBase* dataBase);

    FilePlayList fromSqlQuery(QSharedPointer<QSqlQuery> query);

protected:
    QString getTableCreateQueryText() override;
};

//==============================================================================
}

#endif // FILEPLAYLISTTABLE_H
