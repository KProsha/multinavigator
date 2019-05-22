#ifndef TEXTVALUE_H
#define TEXTVALUE_H

#include <QSettings>
#include <QSharedPointer>

class TextValue
{  
  QSharedPointer<QSettings> settings;

  QString getValue(const QString& key);

public: 
  TextValue(const QString& fileName, QObject *parent = nullptr);

  static TextValue* I;

  void setFileName(const QString& fileName);

  QString directory(){return getValue("common/Directory");}
  QString openDirectory(){return getValue("common/OpenDirectory");}
  QString noDirectory(){return getValue("common/NoDirectory");}

  QString file(){return getValue("common/File");}

  QString filters(){return getValue("common/Filters");}
};

#endif // TEXTVALUE_H
