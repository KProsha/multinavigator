#ifndef FILETAGTABLE_H
#define FILETAGTABLE_H

#include "table.h"
#include "filetag.h"

#include <QList>

namespace database {
//==============================================================================

class FileTagTable : public Table
{
protected:

  FileTag *fromSqlQuery(QSqlQuery* query);
  void prepareInsertSqlQuery(QSqlQuery* query, Record* record);

  QString getTableCreateQueryText();
public:
  FileTagTable();

  QSharedPointer<FileTag> addFileTag(int fileId, int tagId);



};
//==============================================================================
}


#endif // FILETAGTABLE_H
