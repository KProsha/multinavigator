#include "filetagtable.h"


namespace database {
//==============================================================================




FileTagTable::FileTagTable():Table("fileTag")
{

}

//------------------------------------------------------------------------------
QString FileTagTable::getTableCreateQueryText()
{
  QString QueryText = QString(
      "CREATE TABLE %1 (Id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
      "FileId  INTEGER,"
      "TagId   INTEGER"
      ")").arg(name);
  return QueryText;
}
//------------------------------------------------------------------------------
void FileTagTable::prepareInsertSqlQuery(QSqlQuery* query, Record* record)
{
  FileTag* FileTagI = static_cast<FileTag*>(record);

  query->prepare(QString("INSERT INTO %1(FileId,TagId)  VALUES(?,?)").arg(name)
                );

  query->addBindValue(FileTagI->fileId);
  query->addBindValue(FileTagI->tagId);

}
//------------------------------------------------------------------------------
FileTag* FileTagTable::fromSqlQuery(QSqlQuery *query)
{
  bool ReadOk = true;
  bool Ok;
  int Id = query->value(0).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  int FileId = query->value(1).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  int TagId = query->value(2).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  if(!ReadOk) return nullptr;

  auto RecordI = new FileTag();
  RecordI->id = Id;
  RecordI->fileId = FileId;
  RecordI->tagId = TagId;

  return RecordI;
}
//------------------------------------------------------------------------------
QSharedPointer<FileTag> FileTagTable::addFileTag(int fileId, int tagId)
{
  auto fileTag = QSharedPointer<FileTag>(new FileTag());
  fileTag->fileId = fileId;
  fileTag->tagId  = tagId;

  insertRecord(&*fileTag);

  return fileTag;
}


//==============================================================================
}
