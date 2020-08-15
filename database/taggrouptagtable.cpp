#include "taggrouptagtable.h"

#include "database.h"

namespace database {
//==============================================================================

TagGroupTagTable::TagGroupTagTable(DataBase* dataBase):Table(dataBase)
{

}
//------------------------------------------------------------------------------
void TagGroupTagTable::toggleTagGroupTag(quint64 tagGroupId, quint64 tagId, bool enable)
{
    auto query = dataBase->query();
    query->prepare("INSERT INTO taggrouptag (tagGroupId, tagId, enable) VALUES(?, ?, 1) "
                   "ON CONFLICT (tagGroupId, tagId) DO UPDATE SET enable = ?"
                   );

    query->addBindValue(tagGroupId);
    query->addBindValue(tagId);
    query->addBindValue(enable);

    query->exec();
}
//------------------------------------------------------------------------------
void database::TagGroupTagTable::deleteTagGroupTagByGroup(quint64 groupId)
{
    auto query = dataBase->query();
    query->prepare("DELETE FROM taggrouptag WHERE tagGroupId = ?");
    query->addBindValue(groupId);

    query->exec();
}
//------------------------------------------------------------------------------
void TagGroupTagTable::deleteTagGroupTagByTag(quint64 tagId)
{
    auto query = dataBase->query();
    query->prepare("DELETE FROM taggrouptag WHERE tagId = ?");
    query->addBindValue(tagId);

    query->exec();
}
//------------------------------------------------------------------------------
QList<quint64> database::TagGroupTagTable::getTagGroupsId(quint64 tagGroup)
{
    QList<quint64> res;

    auto query = dataBase->query();
    query->prepare("SELECT tagGroupId FROM taggrouptag WHERE tagId=? AND enable <> 0");
    query->addBindValue(tagGroup);

    if(!query->exec()) return res;

    bool ok;
    while (query->next()) {
        quint64 id = query->value(0).toULongLong(&ok);
        if(ok) res.append(id);
    }

    return res;
}
//------------------------------------------------------------------------------
TagGroupTag TagGroupTagTable::fromSqlQuery(QSharedPointer<QSqlQuery> query)
{
    TagGroupTag res;

//    res.setId(query->value(0).toULongLong());
//    res.setName(query->value(1).toString());

    return res;
}
//------------------------------------------------------------------------------
QString TagGroupTagTable::getTableCreateQueryText()
{
    QString queryText = QStringLiteral("CREATE TABLE taggrouptag (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                       "tagGroupId  INTEGER,"
                                       "tagId   INTEGER,"
                                       "enable  INTEGER,"
                                       "UNIQUE (tagGroupId, tagId)"
                                       ")");
    return queryText;
}

//==============================================================================
}


