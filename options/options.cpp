#include "options.h"

Options* Options::i = nullptr;

Options::Options(const QString& fileName, QObject *parent):
  QSettings(fileName,QSettings::IniFormat, parent)
{
  load();

  i = this;
}
//------------------------------------------------------------------------------
void Options::load()
{
  databaseFileName = value("File/DatabaseFileName", "database.db").toString();

  beginGroup("Suffix");
  suffixList = childKeys();

  endGroup();

}
