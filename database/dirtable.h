#ifndef DIRTABLE_H
#define DIRTABLE_H

#include "table.h"
#include "types/dir.h"

namespace database {
//==============================================================================

class DirTable: public Table
{

public:
    DirTable(DataBase* dataBase);

    bool addDirAndGetId(Dir& dir);

    Dir getRootDir();

    Dir getDir(int id);
    Dir fromSqlQuery(QSharedPointer<QSqlQuery> query);

    int getId(const QString& relativePath);
protected:
    QString getTableCreateQueryText() override;




};
//==============================================================================
}
#endif // DIRTABLE_H
