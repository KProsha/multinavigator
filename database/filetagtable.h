#ifndef FILETAGTABLE_H
#define FILETAGTABLE_H

#include "table.h"
#include "types/filetag.h"

#include <QList>

namespace database {
//==============================================================================

class FileTagTable : public Table
{

public:
    FileTagTable(database::DataBase* dataBase);

    void toggleFileTag(int fileId, int tagId);
    void addFileTag(int fileId, int tagId);
    void deleteRecord(int tagId);

protected:
    FileTag fromSqlQuery(QSharedPointer<QSqlQuery> query);
    QString getTableCreateQueryText() override;
};
//==============================================================================
}


#endif // FILETAGTABLE_H
