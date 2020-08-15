#ifndef TAGGROUPTABLE_H
#define TAGGROUPTABLE_H

#include "table.h"
#include "types/taggroup.h"

namespace database {
//==============================================================================

class TagGroupTable: public Table
{
public:
    TagGroupTable(DataBase* dataBase);

    void addGroup(const QString& name);
    int addGroupAndGetId(const QString& name);
    void deleteGroup(quint64 id);
    bool rename(quint64 tagId, const QString& newName);

    QList<TagGroup> getAllTagGroupList();

protected:
    TagGroup fromSqlQuery(QSharedPointer<QSqlQuery> query);
    QString getTableCreateQueryText() override;
};

//==============================================================================
}


#endif // TAGGROUPTABLE_H
