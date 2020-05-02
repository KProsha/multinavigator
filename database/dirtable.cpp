#include "dirtable.h"

#include "database.h"

namespace database {
//==============================================================================

DirTable::DirTable(DataBase* dataBase):Table(dataBase)
{

}
//------------------------------------------------------------------------------
QString DirTable::getTableCreateQueryText()
{
    QString QueryText = QStringLiteral("CREATE TABLE directory (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                       "name         TEXT,"
                                       "relativePath TEXT,"
                                       "type         INTEGER,"
                                       "parentDirId  INTEGER,"
                                       "UNIQUE (name,parentDirId)"
                                       ")");
    return QueryText;
}
//------------------------------------------------------------------------------
Dir DirTable::fromSqlQuery(QSharedPointer<QSqlQuery> query)
{
    int i = 0;

    Dir res;

    res.setId(query->value(i++).toInt());
    res.setName(query->value(i++).toString());
    res.setRelativePath(query->value(i++).toString());
    res.setType(static_cast<Dir::EType>(query->value(i++).toInt()));
    res.setParentId(query->value(i++).toInt());

    return res;
}
//------------------------------------------------------------------------------
int DirTable::getId(const QString& relativePath)
{
    auto query = dataBase->query();
    query->prepare("SELECT id FROM directory WHERE relativePath=?");
    query->addBindValue(relativePath);

    if(query->exec() && query->first()){
        return query->value(0).toInt();
    }

    return -1;
}
//------------------------------------------------------------------------------
bool DirTable::addDirAndGetId(Dir& dir)
{
    auto query = dataBase->query();

    query->prepare("INSERT INTO directory(type,name,relativePath,parentDirId)  VALUES(?,?,?,?)");

    query->addBindValue(static_cast<int>(dir.getType()));
    query->addBindValue(dir.getName());
    query->addBindValue(dir.getRelativePath());
    query->addBindValue(dir.getParentId());

    if(!dataBase->transaction()) return  false;

    if(!query->exec()){
        dataBase->rollback();
        //        qDebug() << "Sql insert query : '" << query->lastQuery() << "' error:" << query->lastError().text();
        return false;
    }

    auto lastIdQuery = dataBase->query();

    if(!lastIdQuery->exec(QStringLiteral("SELECT last_insert_rowid();"))){
        dataBase->rollback();
        //        qDebug() << "Sql query: '" << query->lastQuery() << "' error:" << query->lastError().text();
        return false;
    }
    lastIdQuery->next();

    dir.setId(lastIdQuery->value(0).toInt());
    dataBase->commit();

    return true;
}
//------------------------------------------------------------------------------
Dir DirTable::getRootDir()
{
    Dir res;
    auto query = sendQuery("SELECT * FROM directory WHERE type = 1");
    if(!query.isNull()  &&  query->first())
        res = fromSqlQuery(query);
    return res;
}
//------------------------------------------------------------------------------
Dir DirTable::getDir(int id)
{
    Dir res;
    auto query = sendQuery((QString("SELECT * FROM directory WHERE Id = %2").arg(id)));
    if(!query.isNull()  &&  query->first()){
        res = fromSqlQuery(query);
    }
    return res;
}

//==============================================================================
}
