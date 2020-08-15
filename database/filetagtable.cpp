#include "filetagtable.h"

#include "database.h"

namespace database {
//==============================================================================

FileTagTable::FileTagTable(DataBase* dataBase):Table(dataBase)
{

}

//------------------------------------------------------------------------------
QString FileTagTable::getTableCreateQueryText()
{
    QString queryText = QStringLiteral("CREATE TABLE fileTag (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                       "fileId  INTEGER,"
                                       "tagId   INTEGER,"
                                       "enable  INTEGER,"
                                       "UNIQUE (fileId, tagId)"
                                       ")");
    return queryText;
}
//------------------------------------------------------------------------------
FileTag FileTagTable::fromSqlQuery(QSharedPointer<QSqlQuery> query)
{
    int i = 0;

    FileTag record;

    record.setId(query->value(i++).toInt());
    record.setFileId(query->value(i++).toInt());
    record.setTagId(query->value(i++).toInt());
    record.setEnable(query->value(i++).toBool());

    return record;
}
//------------------------------------------------------------------------------
void FileTagTable::toggleFileTag(int fileId, int tagId)
{    
    auto query = dataBase->query();
    query->prepare("INSERT INTO fileTag (fileId,tagId,enable)  VALUES(?,?,1) "
                   "ON CONFLICT (fileId, tagId) DO UPDATE SET enable = CASE WHEN (enable = 0) THEN 1 ELSE 0 END "
                   );

    query->addBindValue(fileId);
    query->addBindValue(tagId);

    query->exec();
}
//------------------------------------------------------------------------------
void FileTagTable::addFileTag(int fileId, int tagId)
{
    auto query = dataBase->query();
    query->prepare("INSERT INTO fileTag (fileId,tagId,enable)  VALUES(?,?,1)");

    query->addBindValue(fileId);
    query->addBindValue(tagId);

    query->exec();
}
//------------------------------------------------------------------------------
void FileTagTable::deleteRecord(int tagId)
{
    auto query = dataBase->query();
    query->prepare("DELETE FROM fileTag WHERE tagId = ?");
    query->addBindValue(tagId);

    query->exec();
}


//==============================================================================
}
