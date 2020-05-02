#ifndef TEXTVALUE_H
#define TEXTVALUE_H

#include <QSettings>
#include <QSharedPointer>

class TextValue
{  
    QSharedPointer<QSettings> settings;

public:
    TextValue(const QString& fileName);

    void setFileName(const QString& fileName);

    QString getValue(const QString& key);


};

#endif // TEXTVALUE_H
