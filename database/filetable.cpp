#include "filetable.h"

#include "backend/appglobal.h"

namespace database {
//==============================================================================

FileTable::FileTable(DataBase* dataBase):Table(dataBase)
{
    tableName = QStringLiteral("file");
}

//------------------------------------------------------------------------------
QString FileTable::getTableCreateQueryText()
{
    QString QueryText = QStringLiteral(
                "CREATE TABLE file (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "created TIMESTAMP,"
                "type TEXT,"
                "name TEXT,"
                "size INTEGER,"
                "dirId INTEGER,"
                "comment TEXT,"
                "UNIQUE (dirId,name) ON CONFLICT FAIL "
                ")");
    return QueryText;
}

//------------------------------------------------------------------------------
File FileTable::fromSqlQuery(QSharedPointer<QSqlQuery> query)
{
    int i = 0;

    File res;

    res.setId(query->value(i++).toInt());
    res.setCreated(query->value(i++).toDateTime());
    res.setType(query->value(i++).toString());
    res.setName(query->value(i++).toString());
    res.setSize(query->value(i++).toInt());
    res.setDirId(query->value(i++).toInt());
    res.setComment(query->value(i++).toString());

    return res;
}
//------------------------------------------------------------------------------
bool FileTable::addFile(File& file)
{
    auto query = dataBase->query();
    query->prepare(QStringLiteral("INSERT INTO file(created,type,name,size,dirId,comment) "
                                  "VALUES(?,?,?,?,?,?) "));

    query->addBindValue(file.getCreated());
    query->addBindValue(file.getType());
    query->addBindValue(file.getName());
    query->addBindValue(file.getSize());
    query->addBindValue(file.getDirId());
    query->addBindValue(file.getComment());

    if(!query->exec()) return  false;
    return true;
}
//------------------------------------------------------------------------------
bool FileTable::addFileAndGetId(File& file)
{
    auto query = dataBase->query();
    query->prepare(QStringLiteral("INSERT INTO file(created,type,name,size,dirId,comment) "
                                  "VALUES(?,?,?,?,?,?) "));

    query->addBindValue(file.getCreated());
    query->addBindValue(file.getType());
    query->addBindValue(file.getName());
    query->addBindValue(file.getSize());
    query->addBindValue(file.getDirId());
    query->addBindValue(file.getComment());

    if(!query->exec()){
        auto searchIdQuery = sendQuery((QStringLiteral("SELECT id FROM file WHERE dirId = %1 AND name = \"%2\"").
                                        arg(file.getDirId())).
                                        arg(file.getName()));
        if(!searchIdQuery.isNull()  &&  searchIdQuery->first()){
            bool ok;
            file.setId(searchIdQuery->value(0).toInt(&ok));
            if(!ok) file.setId(-1);
        }

        return false;
    }

    auto lastIdQuery = dataBase->query();

    if(!lastIdQuery->exec(QStringLiteral("SELECT last_insert_rowid();"))){
        return false;
    }
    lastIdQuery->next();
    file.setId(lastIdQuery->value(0).toInt());

    return true;
}
//------------------------------------------------------------------------------
QList<File> FileTable::getFileList(QList<quint64> fileIdList)
{
    QList<File> res;

    QStringList idStringList;
    foreach (quint64 id, fileIdList) {
        idStringList.append(QString::number(id));
    }

    auto query = sendQuery(QStringLiteral("SELECT * FROM file WHERE Id IN (%1)")
                           .arg(idStringList.join(',')));
    if(query.isNull()) return res;

    while (query->next()) {
        res.append(fromSqlQuery(query));
    }

    return res;
}
//------------------------------------------------------------------------------
QList<File> FileTable::getAllFiles()
{
    QList<File> res;
    auto query = sendQuery(QStringLiteral("SELECT * FROM file"));
    if(query.isNull()) return res;

    while (query->next()) {
        res.append(fromSqlQuery(query));
    }

    return res;
}
//------------------------------------------------------------------------------
File FileTable::getFile(int id)
{
    File res;
    auto query = sendQuery((QString("SELECT * FROM file WHERE id = %2").arg(id)));
    if(!query.isNull()  &&  query->first()){
        res = fromSqlQuery(query);
    }
    return res;
}

//==============================================================================
}

