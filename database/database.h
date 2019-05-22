#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutexLocker>

#include "filetable.h"
#include "filetagtable.h"
#include "tagtable.h"
#include "dirtable.h"

namespace database {
//==============================================================================

class DataBase : public QObject
{
  Q_OBJECT

  QString dirName;

  QSqlDatabase sqlDataBbase;

  QMutex* databaseMutex;

  void configDB();

  int scanSubDir(const QString& name, const QString &parendDirPath = "", int parentDirId = -1);
//  void read();
public:
  explicit DataBase(QObject *parent = nullptr);
  ~DataBase();

  bool openDir(const QString& name);

  static DataBase* i;

  bool connect();
  void disconnect();

  QSharedPointer<QSqlQuery> sendQuery(const QString& queryText);

  QSharedPointer<FileTable> fileTable;
  QSharedPointer<TagTable> tagTable;
  QSharedPointer<FileTagTable> fileTagTable;
  QSharedPointer<DirTable> dirTable;

  QSqlDatabase& getSqlDataBbase(){return sqlDataBbase;}

  void addRootDir(const QString& name);


signals:
  void sigDirUpdateEvent(int dirId);

};
//==============================================================================
}
#endif // DATABASE_H
