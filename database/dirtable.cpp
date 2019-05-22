#include "dirtable.h"

#include "database.h"

namespace database {
//==============================================================================

DirTable::DirTable():Table("directory")
{

}
//------------------------------------------------------------------------------
QString DirTable::getTableCreateQueryText()
{
  QString QueryText = QString(
        "CREATE TABLE %1 (Id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
        "Name        TEXT,"
        "Type        INTEGER,"
        "ParentDirId INTEGER,"
        "Comment     TEXT"
        ")").arg(name);
  return QueryText;
}
//------------------------------------------------------------------------------
Dir* DirTable::fromSqlQuery(QSqlQuery *query)
{
  bool ReadOk = true;
  bool Ok;
  int Id = query->value(0).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  QString Name = query->value(1).toString();

  int Type = query->value(2).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  int ParentId = query->value(3).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  QString Comment = query->value(4).toString();

  if(!ReadOk) return nullptr;

  auto RecordI = new Dir();
  RecordI->id = Id;
  RecordI->name = Name;
  RecordI->type = (Dir::EType)Type;
  RecordI->parentId = ParentId;
  RecordI->comment = Comment;

  return RecordI;
}
//------------------------------------------------------------------------------
void DirTable::prepareInsertSqlQuery(QSqlQuery* query, Record* record)
{
  Dir* DirI = static_cast<Dir*>(record);

  query->prepare(QString("INSERT INTO %1(Type,Name,ParentDirId,Comment)  VALUES(?,?,?,?)").arg(name)
                 );

  query->addBindValue((int)DirI->type);
  query->addBindValue(DirI->name);
  query->addBindValue(DirI->parentId);
  query->addBindValue(DirI->comment);
}
//------------------------------------------------------------------------------
//QSharedPointer<Dir> DirTable::getRootDir()
//{
//  QSharedPointer<Dir> res;
//  auto query = sendQuery("SELECT * FROM Dir WHERE Type=" + QString::number(Dir::TypeRoot));

//  while (query->next()) {
//    res = QSharedPointer<Dir>(fromSqlQuery(&*query));
//  }
//  return res;
//}
////------------------------------------------------------------------------------
//bool DirTable::hasRootDir()
//{
//  auto rootDir = getRootDir();

//  if(rootDir.isNull())return false;

//  return true;
//}

//------------------------------------------------------------------------------
QSharedPointer<Dir> DirTable::addDir(Dir::EType type,
                                     const QString &name,
                                     int parentId,
                                     const QString &comment)
{
  auto dir = QSharedPointer<Dir>(new Dir());
  dir->name = name;
  dir->type = type;
  dir->parentId = parentId;
  dir->comment = comment;

  insertRecord(&*dir);

  return dir;
}



//==============================================================================
}
