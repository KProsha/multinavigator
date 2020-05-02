#ifndef TAGTABLE_H
#define TAGTABLE_H

#include "table.h"

#include "types/tag.h"

#include "dirtable.h"

namespace database {
//==============================================================================

class TagTable : public Table
{


public:
    TagTable(database::DataBase* dataBase);

    void addTag(const QString& name, Tag::EType type);
    int addTagAndGetId(const QString& name, Tag::EType type);
    bool renameTag(int tagId, const QString& newName);
    void deleteTag(int tagId);

    QList<Tag> getAllTags();

protected:

    Tag fromSqlQuery(QSharedPointer<QSqlQuery> query);
    QString getTableCreateQueryText() override;

    friend class DataBase;

};
//==============================================================================
}
#endif // TAGTABLE_H
