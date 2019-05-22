#include "tagtable.h"


namespace database {
//==============================================================================

TagTable::TagTable():Table("tag")
{

}
//------------------------------------------------------------------------------
QString TagTable::getTableCreateQueryText()
{
  QString QueryText = QString(
             "CREATE TABLE %1 (Id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
             "Name INTEGER,"
             "Type INTEGER,"
             "Comment  TEXT"
             ")").arg(name);
     return QueryText;
}
//------------------------------------------------------------------------------
void TagTable::prepareInsertSqlQuery(QSqlQuery* query, Record* record)
{
  Tag* TagI = static_cast<Tag*>(record);

  query->prepare(QString("INSERT INTO %1(Name,Type,Comment)  VALUES(?,?,?)").arg(name)
                );

  query->addBindValue(TagI->name);
  query->addBindValue((int)TagI->type);
  query->addBindValue(TagI->comment);
}
//------------------------------------------------------------------------------
Tag* TagTable::fromSqlQuery(QSqlQuery *query)
{
  bool ReadOk = true;
  bool Ok;
  int Id = query->value(0).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  QString Name = query->value(1).toString();

  int Type = query->value(2).toInt(&Ok);
  ReadOk = Ok && ReadOk;

  QString Comment = query->value(3).toString();

  if(!ReadOk) return nullptr;

  auto RecordI = new Tag();
  RecordI->id = Id;
  RecordI->name = Name;
  RecordI->type = (Tag::EType)Type;
  RecordI->comment = Comment;

  return RecordI;
}

//------------------------------------------------------------------------------
QSharedPointer<Tag> TagTable::addTag(const QString& name, Tag::EType type, const QString& comment)
{
  auto TagI = QSharedPointer<Tag>(new Tag());
  TagI->name    = name;
  TagI->type    = type;
  TagI->comment = comment;

  insertRecord(&*TagI,true);

  return TagI;
}
//------------------------------------------------------------------------------
bool TagTable::isUnuque(Record* record)
{
  Tag* TagI = static_cast<Tag*>(record);
  auto RecordList = getRecords<Tag>(TagI->name);

  if(RecordList.isEmpty()) return  true;

  return false;
}


//==============================================================================
}
