#include "options.h"

Options::Options(const QString& fileName, QObject *parent):
    QSettings(fileName,QSettings::IniFormat, parent)
{
    load();
}
//------------------------------------------------------------------------------
void Options::load()
{
    databaseFileName = value("file/DatabaseFileName", "database.db").toString();

    beginGroup("suffix");
    suffixList = childKeys();

    endGroup();
}
//------------------------------------------------------------------------------
QStringList Options::getSuffixList() const
{
    return suffixList;
}
//------------------------------------------------------------------------------
QString Options::getDatabaseFileName() const
{
    return databaseFileName;
}
