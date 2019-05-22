#include "table.h"

#include "database.h"

namespace database {
//==============================================================================

QSharedPointer<QSqlQuery> Table::sendQuery(const QString& text)
{
  if(!DataBase::i->connect()) return QSharedPointer<QSqlQuery>(nullptr);

  QSharedPointer<QSqlQuery> query =  QSharedPointer<QSqlQuery>(new QSqlQuery(DataBase::i->getSqlDataBbase()));

  query->exec(text);

  return query;
}
//------------------------------------------------------------------------------
QList<QSharedPointer<Record> > Table::readAllFromDataBase()
{
  QList<QSharedPointer<Record> > recordList;

  auto query = sendQuery("SELECT * FROM " + name);
  if(!query->isValid()) return recordList;
  while (query->next()) {
    recordList.append(QSharedPointer<Record>(fromSqlQuery(&*query)));
  }
  return recordList;
}
//------------------------------------------------------------------------------
bool Table::insertRecord(Record* record, bool insertIfUnuque)
{
  if(insertIfUnuque && (!isUnuque(record))) return false;

  if( (!DataBase::i->connect()) || (!DataBase::i->getSqlDataBbase().transaction()) ) return  -1;

  QSqlQuery query(DataBase::i->getSqlDataBbase());

  prepareInsertSqlQuery(&query, record);

  if(!query.exec()){
    DataBase::i->getSqlDataBbase().rollback();
    return false;
  }

  QSqlQuery lastIdQuery(DataBase::i->getSqlDataBbase());
  if(!lastIdQuery.exec("SELECT last_insert_rowid();")){
    DataBase::i->getSqlDataBbase().rollback();
    return false;
  }
  lastIdQuery.next();

  record->id = lastIdQuery.value(0).toInt();
  DataBase::i->getSqlDataBbase().commit();

  return true;
}

//==============================================================================
}


