#include "filetable.h"

namespace database {
//==============================================================================

FileTable::FileTable():Table("file")
{

}
//------------------------------------------------------------------------------
QString FileTable::getTableCreateQueryText()
{
  QString QueryText = QString(
        "CREATE TABLE %1 (Id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
        "Created TIMESTAMP,"
        "LastModified TIMESTAMP,"
        "Registered TIMESTAMP,"
        "Type     Text,"
        "Name   Text,"
        "Size INTEGER,"
        "DirId INTEGER,"
        "Comment  TEXT"
        ")").arg(name);
  return QueryText;
}
//------------------------------------------------------------------------------
void FileTable::prepareInsertSqlQuery(QSqlQuery* query, Record* record)
{
  File* FileI = static_cast<File*>(record);

  query->prepare(QString("INSERT INTO %1(Created,LastModified,Registered,Type,Name,Size,DirId,Comment) "
                         "VALUES(?,?,?,?,?,?,?,?)").arg(name)
                 );

  query->addBindValue(FileI->created);
  query->addBindValue(FileI->lastModified);
  query->addBindValue(FileI->registered);
  query->addBindValue(FileI->type);
  query->addBindValue(FileI->name);
  query->addBindValue(FileI->size);
  query->addBindValue(FileI->dirId);
  query->addBindValue(FileI->comment);
}

//------------------------------------------------------------------------------
File* FileTable::fromSqlQuery(QSqlQuery *query)
{
  bool ReadOk = true;
  bool Ok;
  int Id = query->value(0).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  int i = 0;
  QDateTime Created = query->value(i++).toDateTime();
  QDateTime LastModified = query->value(i++).toDateTime();
  QDateTime Registered = query->value(i++).toDateTime();

  QString Type = query->value(i++).toString();

  QString Name = query->value(i++).toString();

  int Size = query->value(i++).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  int DirId = query->value(i++).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  QString Comment = query->value(i++).toString();

  if(!ReadOk) return nullptr;


  auto RecordI = new File();
  RecordI->id = Id;
  RecordI->name = Name;
  RecordI->type = Type;
  RecordI->created = Created;
  RecordI->lastModified = LastModified;
  RecordI->registered = Registered;
  RecordI->size = Size;
  RecordI->dirId = DirId;
  RecordI->comment = Comment;

  return RecordI;
}
//------------------------------------------------------------------------------
QSharedPointer<File> FileTable::addFile(const QDateTime &created,
                                        const QDateTime &lastModified,
                                        const QDateTime &registered,
                                        QString type,
                                        QString  name,
                                        qint64 size,
                                        int dirId,
                                        const QString& comment)
{
  auto res = QSharedPointer<File>(new File());
  res->created    = created;
  res->lastModified = lastModified;
  res->registered = registered;
  res->name = name;
  res->type = type;
  res->size  = size;
  res->dirId = dirId;
  res->comment = comment;

  insertRecord(&*res);

  return res;
}



//==============================================================================
}

//------------------------------------------------------------------------------
//void CAction::fromSqlQuery(const QSqlQuery& query)
//{
//    bool ok;
//    Id = query.value(0).toInt(&ok);
//    DateTime = query.value(1).toDateTime();
//    Type     = (CAction::EType)query.value(2).toInt(&ok);
//    UserId   = query.value(3).toInt(&ok);
//    ValueId  = query.value(4).toInt(&ok);
//    Comment  = query.value(5).toString();
//}
////------------------------------------------------------------------------------
//void CAction::prepareInsertQuery(QSqlQuery& query)
//{
//    query.prepare("INSERT INTO actions(DateTime, Type, UserId, ValueId, Comment)"
//                  "VALUES (?, ?, ?, ?, ?)");
//    query.addBindValue(QDateTime::currentDateTime());
//    query.addBindValue(Type);
//    query.addBindValue(UserId);
//    query.addBindValue(ValueId);
//    query.addBindValue(Comment);
//}
