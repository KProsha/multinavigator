#ifndef TAGTABLE_H
#define TAGTABLE_H

#include "table.h"

#include "tag.h"

#include "dirtable.h"

namespace database {
//==============================================================================

class TagTable : public Table
{
protected:

  Tag *fromSqlQuery(QSqlQuery* query);
  void prepareInsertSqlQuery(QSqlQuery* query, Record* record);

  bool isUnuque(Record* record);

  QString getTableCreateQueryText();
public:
  TagTable();

  QSharedPointer<Tag> addTag(const QString& name, Tag::EType type, const QString& comment = "");

  QList<QSharedPointer<Tag> > getTagList(){return getRecords<Tag>();}

};
//==============================================================================
}
#endif // TAGTABLE_H
