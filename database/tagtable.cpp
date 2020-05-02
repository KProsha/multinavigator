#include "tagtable.h"

#include "backend/appglobal.h"

namespace database {
//==============================================================================

TagTable::TagTable(DataBase* dataBase):Table(dataBase)
{

}
//------------------------------------------------------------------------------
QString TagTable::getTableCreateQueryText()
{
    QString QueryText = QStringLiteral("CREATE TABLE tag(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                       "name TEXT UNIQUE,"
                                       "type INTEGER"
                                       ")");
    return QueryText;
}
//------------------------------------------------------------------------------
Tag TagTable::fromSqlQuery(QSharedPointer<QSqlQuery> query)
{    
    Tag res;

    res.setId(query->value(0).toInt());
    res.setName(query->value(1).toString());
    res.setType(static_cast<Tag::EType>(query->value(2).toInt()));

    return res;
}
//------------------------------------------------------------------------------
void TagTable::addTag(const QString& name, Tag::EType type)
{
    auto query = dataBase->query();
    query->prepare("INSERT INTO tag(name,type)  VALUES(?,?)");

    query->addBindValue(name);
    query->addBindValue(static_cast<int>(type));

    query->exec();
}
//------------------------------------------------------------------------------
int TagTable::addTagAndGetId(const QString& name, Tag::EType type)
{
    int res = -1;
    auto query = dataBase->query();
    query->prepare("INSERT INTO tag(name,type)  VALUES(?,?)");

    query->addBindValue(name);
    query->addBindValue(static_cast<int>(type));

    if(!query->exec()){
        auto searchIdQuery = sendQuery((QStringLiteral("SELECT id FROM tag WHERE name = \"%1\"").
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
bool TagTable::renameTag(int tagId, const QString& newName)
{
    auto query = dataBase->query();
    query->prepare("UPDATE tag SET name = ? WHERE id = ?");

    query->addBindValue(newName);
    query->addBindValue(tagId);

    if(query->exec()) return true;

    return false;
}
//------------------------------------------------------------------------------
void TagTable::deleteTag(int tagId)
{
    auto query = dataBase->query();
    query->prepare("DELETE FROM  tag WHERE id = ?");
    query->addBindValue(tagId);

    query->exec();
}
//------------------------------------------------------------------------------
QList<Tag> TagTable::getAllTags()
{
    QList<Tag> res;
    auto query = sendQuery(QStringLiteral("SELECT * FROM tag"));
    if(query.isNull()) return res;

    while (query->next()) {
        res.append(fromSqlQuery(query));
    }

    return res;
}

//==============================================================================
}
