#include "taggrouptable.h"

#include "database.h"

namespace database {
//==============================================================================

TagGroupTable::TagGroupTable(DataBase* dataBase):Table(dataBase)
{

}
//------------------------------------------------------------------------------
void TagGroupTable::addGroup(const QString& name)
{
    auto query = dataBase->query();
    query->prepare("INSERT INTO taggroup(name) VALUES(?)");

    query->addBindValue(name);

    query->exec();
}
//------------------------------------------------------------------------------
int TagGroupTable::addGroupAndGetId(const QString& name)
{
    int res = -1;
    auto query = dataBase->query();
    query->prepare("INSERT INTO taggroup(name)  VALUES(?)");

    query->addBindValue(name);

    if(!query->exec()){
        auto searchIdQuery = sendQuery((QStringLiteral("SELECT id FROM taggroup WHERE name = \"%1\"").
                                        arg(name)));
        if(!searchIdQuery.isNull()  &&  searchIdQuery->first()){
            bool ok;
            res = searchIdQuery->value(0).toInt(&ok);
            if(!ok) res = -1;
        }
        return -1;
    }

    auto lastIdQuery = dataBase->query();

    if(!lastIdQuery->exec(QStringLiteral("SELECT last_insert_rowid();"))){
        return -1;
    }
    lastIdQuery->next();
    res = lastIdQuery->value(0).toInt();

    return res;
}
//------------------------------------------------------------------------------
void TagGroupTable::deleteGroup(quint64 id)
{
    auto query = dataBase->query();
    query->prepare("DELETE FROM taggroup WHERE id = ?");
    query->addBindValue(id);

    query->exec();
}
//------------------------------------------------------------------------------
bool database::TagGroupTable::rename(quint64 tagId, const QString& newName)
{
    auto query = dataBase->query();
    query->prepare("UPDATE taggroup SET name = ? WHERE id = ?");

    query->addBindValue(newName);
    query->addBindValue(tagId);

    if(query->exec()) return true;

    return false;
}
//------------------------------------------------------------------------------
QList<TagGroup> TagGroupTable::getAllTagGroupList()
{
    QList<TagGroup> res;
    auto query = sendQuery(QStringLiteral("SELECT * FROM taggroup"));

    while (query->next()) {
        res.append(fromSqlQuery(query));        
    }
    return res;
}
//------------------------------------------------------------------------------
TagGroup TagGroupTable::fromSqlQuery(QSharedPointer<QSqlQuery> query)
{
    TagGroup res;

    res.setId(query->value(0).toULongLong());
    res.setName(query->value(1).toString());

    return res;
}
//------------------------------------------------------------------------------
QString TagGroupTable::getTableCreateQueryText()
{
    QString QueryText = QStringLiteral("CREATE TABLE taggroup(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                       "name TEXT UNIQUE"
                                       ")");
    return QueryText;
}


//==============================================================================
}
