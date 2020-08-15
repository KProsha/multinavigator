#ifndef TAGGROUPTAGTABLE_H
#define TAGGROUPTAGTABLE_H

#include "table.h"
#include "types/taggrouptag.h"

namespace database {
//==============================================================================

class TagGroupTagTable: public Table
{
public:
    TagGroupTagTable(DataBase* dataBase);

    void toggleTagGroupTag(quint64 tagGroupId, quint64 tagId, bool enable = true);
    void deleteTagGroupTagByTag(quint64 tagId);
    void deleteTagGroupTagByGroup(quint64 groupId);

    QList<quint64> getTagGroupsId(quint64 tagGroup);

protected:
    TagGroupTag fromSqlQuery(QSharedPointer<QSqlQuery> query);
    QString getTableCreateQueryText() override;
};


//==============================================================================
}


#endif // TAGGROUPTAGTABLE_H
