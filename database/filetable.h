#ifndef FILETABLE_H
#define FILETABLE_H

#include "table.h"

#include <QList>

#include "file.h"

//#include "dirtable.h"

namespace database {
//==============================================================================
class Dir;

class FileTable : public Table
{
protected:

  File* fromSqlQuery(QSqlQuery* query);
  void prepareInsertSqlQuery(QSqlQuery* query, Record* record);

  QString getTableCreateQueryText();
public:
  FileTable();

  QSharedPointer<File> addFile(const QDateTime& created,
                               const QDateTime& lastModified,
                               const QDateTime& registered,
                               QString type,
                               QString  name,
                               qint64 size,
                               int dirId,
                               const QString& comment = "");

  QList<QSharedPointer<File> > getFileList(const QString& name){return getRecords<File>(name);}
};
//==============================================================================
}


#endif // FILETABLE_H
