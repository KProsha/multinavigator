#ifndef FILETABLE_H
#define FILETABLE_H

#include "table.h"

#include <QList>

#include "types/file.h"

namespace database {
//==============================================================================
class Dir;

class FileTable : public Table
{
public:
    FileTable(DataBase* dataBase);

    bool addFile(File& file);
    bool addFileAndGetId(File& file);

    QList<File> getFileList(QList<quint64> fileIdList);
    QList<File> getAllFiles();
    File getFile(int id);

    File fromSqlQuery(QSharedPointer<QSqlQuery> query);

protected:
     QString getTableCreateQueryText() override;

};
//==============================================================================
}


#endif // FILETABLE_H
