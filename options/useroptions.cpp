#include "useroptions.h"

#include "options.h"

UserOptions::UserOptions(const QString& fileName, QObject *parent):
  QSettings(fileName,QSettings::IniFormat, parent)
{
  load();
}
//------------------------------------------------------------------------------
void UserOptions::save()
{
  setValue("File/RecentDir", recentDir);
}
//------------------------------------------------------------------------------
void UserOptions::load()
{
  recentDir = value("File/RecentDir").toString();
}
//------------------------------------------------------------------------------
const QString &UserOptions::getRecentDir() const
{
  return recentDir;
}
//------------------------------------------------------------------------------
void UserOptions::setRecentDir(const QString &value)
{
  recentDir = value;
}
