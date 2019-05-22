#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QSqlQuery>
#include <QList>
#include <QSharedPointer>

#include "record.h"

namespace database {
//==============================================================================



class Table
{
protected:
  virtual QString getTableCreateQueryText() = 0;

  virtual Record* fromSqlQuery(QSqlQuery* query) = 0;
  virtual void prepareInsertSqlQuery(QSqlQuery* query, Record* record) = 0;

  QSharedPointer<QSqlQuery> sendQuery(const QString& queryText);

  template<typename ELEMENTTYPE>
  QSharedPointer<ELEMENTTYPE>  getRecord(int id) {
    QSharedPointer<ELEMENTTYPE> res;
    auto query = sendQuery((QString("SELECT * FROM %1 WHERE Id=%2").arg(name,id)));
    if(query.isNull()) return res;
    if(query->first()) res = QSharedPointer<ELEMENTTYPE> (static_cast<ELEMENTTYPE*>(fromSqlQuery(&*query)));
    return res;
  }

  template<typename ELEMENTTYPE>
  QList<QSharedPointer<ELEMENTTYPE> > getRecords(const QString& recordName){
    QList<QSharedPointer<ELEMENTTYPE> >  res;
    auto query = sendQuery(QString("SELECT * FROM %1 WHERE Name= '%2'").arg(name,recordName));
    if(query.isNull()) return res;
    while (query->next()) {
      res.append(QSharedPointer<ELEMENTTYPE> (static_cast<ELEMENTTYPE*>(fromSqlQuery(&*query))));
    }
    return res;
  }

  template<typename ELEMENTTYPE>
  QList<QSharedPointer<ELEMENTTYPE> > getRecords(){
    QList<QSharedPointer<ELEMENTTYPE> >  res;
    auto query = sendQuery("SELECT * FROM " + name);
    if(query.isNull()) return res;

    while (query->next()) {
      res.append(QSharedPointer<ELEMENTTYPE> (static_cast<ELEMENTTYPE*>(fromSqlQuery(&*query))));
    }
    return res;
  }

  virtual bool isUnuque(Record* record){(void)record; return true;}
  bool insertRecord(Record* record, bool insertIfUnuque = false);

public:
  QString name;

  Table(const QString& tableName){name = tableName;}
  virtual ~Table(){}


  void createTable(){sendQuery(getTableCreateQueryText());}


  QList<QSharedPointer<Record> > readAllFromDataBase();




};
//==============================================================================
}

#endif // TABLE_H
