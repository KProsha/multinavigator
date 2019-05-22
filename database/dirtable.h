#ifndef DIRTABLE_H
#define DIRTABLE_H

#include "table.h"
#include "dir.h"

#include "filetable.h"


namespace database {
//==============================================================================

class DirTable : public Table
{
protected:

  Dir *fromSqlQuery(QSqlQuery* query);
  void prepareInsertSqlQuery(QSqlQuery* query, Record* record);

  QString getTableCreateQueryText();

public:
  DirTable();

  QSharedPointer<Dir> addDir(Dir::EType type,
                             const QString& name,
                             int parentId,
                             const QString& comment = "");

  QSharedPointer<Dir> getDir(int id){return  getRecord<Dir>(id);}
  QList<QSharedPointer<Dir> > getDirList(const QString& name){return getRecords<Dir>(name);}

//  QSharedPointer<Dir>  getRootDir();
//  bool hasRootDir();

};
//==============================================================================
}
#endif // DIRTABLE_H
