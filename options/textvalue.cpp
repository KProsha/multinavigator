#include "textvalue.h"

TextValue::TextValue(const QString& fileName)
{
    setFileName(fileName);
}
//------------------------------------------------------------------------------
void TextValue::setFileName(const QString& fileName)
{
    settings = QSharedPointer<QSettings>(new QSettings(fileName,QSettings::IniFormat));
}
//------------------------------------------------------------------------------
QString TextValue::getValue(const QString &key)
{
    if(settings.isNull()) return key;

    return settings->value(key).toString();
}
