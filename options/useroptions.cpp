#include "useroptions.h"

#include "options.h"

static const int DEFAULTFILENAMECOUNTFORTAG = 5;
static const int MAXDISPLAYEDTAGLENGTH = 30;

UserOptions::UserOptions(const QString& fileName, QObject *parent):
    QSettings(fileName,QSettings::IniFormat, parent)
{
    load();
}
//------------------------------------------------------------------------------
UserOptions::~UserOptions()
{
   save();
}
//------------------------------------------------------------------------------
void UserOptions::save()
{
    setValue("file/recentDir", recentDir);
    setValue("scanoptions/useDirNameAsTag", useDirNameAsTag);
    setValue("scanoptions/useFileNameAsTag", useFileNameAsTag);
    setValue("scanoptions/fileNameCountForTag", fileNameCountForTag);

}
//------------------------------------------------------------------------------
void UserOptions::load()
{
    bool ok;
    recentDir = value("file/recentDir").toString();
    useDirNameAsTag = value("scanoptions/useDirNameAsTag", true).toBool();
    useFileNameAsTag = value("scanoptions/useFileNameAsTag", true).toBool();
    fileNameCountForTag = value("scanoptions/fileNameCountForTag", DEFAULTFILENAMECOUNTFORTAG).toInt(&ok);
    if(!ok) fileNameCountForTag = DEFAULTFILENAMECOUNTFORTAG;
    maxDisplayedTagLength = value("interface/maxDisplayedTagLength", MAXDISPLAYEDTAGLENGTH).toInt(&ok);
    if(!ok) maxDisplayedTagLength = MAXDISPLAYEDTAGLENGTH;
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
//------------------------------------------------------------------------------
bool UserOptions::getUseDirNameAsTag() const
{
    return useDirNameAsTag;
}
//------------------------------------------------------------------------------
void UserOptions::setUseDirNameAsTag(bool value)
{
    useDirNameAsTag = value;
}
//------------------------------------------------------------------------------
bool UserOptions::getUseFileNameAsTag() const
{
    return useFileNameAsTag;
}
//------------------------------------------------------------------------------
void UserOptions::setUseFileNameAsTag(bool value)
{
    useFileNameAsTag = value;
}
//------------------------------------------------------------------------------
int UserOptions::getFileNameCountForTag() const
{
    return fileNameCountForTag;
}
//------------------------------------------------------------------------------
void UserOptions::setFileNameCountForTag(int value)
{
    fileNameCountForTag = value;
}
//------------------------------------------------------------------------------
bool UserOptions::getUseNumbersAsTag() const
{
    return useNumbersAsTag;
}
//------------------------------------------------------------------------------
void UserOptions::setUseNumbersAsTag(bool value)
{
    useNumbersAsTag = value;
}

int UserOptions::getMaxDisplayedTagLength() const
{
    return maxDisplayedTagLength;
}

void UserOptions::setMaxDisplayedTagLength(int value)
{
    maxDisplayedTagLength = value;
}
