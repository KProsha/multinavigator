#include "appglobal.h"

AppGlobal* AppGlobal::inst = nullptr;

AppGlobal::AppGlobal(QObject *parent):QObject(parent)
{    
    state = StatePlayList;
    pastState = StateFullScreen;

    randomMode = false;
    repeatMode = false;

    optionsInst = new Options("config.ini",this);
    userOptionsInst = new UserOptions("userconfig.ini",this);
    textValueInst = QSharedPointer<TextValue>(new TextValue("textvalue.ini"));

    dataBase = new database::DataBase(this);

    allPlayListModel = new PlayListModel(this);
    customPlayListModel = new PlayListModel(this);
    setCurrentAllPlayListModel();

    connect(dataBase, &database::DataBase::sigFileUpdated, allPlayListModel, &PlayListModel::updatePlaylist);
    connect(dataBase, &database::DataBase::sigFileUpdated, customPlayListModel, &PlayListModel::updatePlaylist);

    connect(allPlayListModel, &PlayListModel::sigNewCurrentFile, this, &AppGlobal::sigNewCurrentFile);
    connect(customPlayListModel, &PlayListModel::sigNewCurrentFile, this, &AppGlobal::sigNewCurrentFile);

    inst = this;
}
//------------------------------------------------------------------------------
void AppGlobal::setNewState(AppGlobal::EAppState newState)
{
    pastState = state;
    state = newState;
    emit sigNewState(state);
}
//------------------------------------------------------------------------------
void AppGlobal::switchFullScreen()
{
    if((pastState == StateFullScreen) || (state == StateFullScreen)){
        std::swap(pastState, state);
        emit sigNewState(state);
    }else{
        pastState = state;
        state = StateFullScreen;
    }
}
//------------------------------------------------------------------------------
void AppGlobal::setTagIdFilter(int id, database::Tag::ESelectionType type)
{
    customPlayListModel->setTagIdFilter(id, type);
}
//------------------------------------------------------------------------------
void AppGlobal::toggleRandomMode()
{
  randomMode = !randomMode;
  emit sigNewRandomMode(randomMode);
}
//------------------------------------------------------------------------------
void AppGlobal::toggleRepeatMode()
{
    repeatMode = !repeatMode;
    emit sigNewRepeatMode(repeatMode);
}
//------------------------------------------------------------------------------
void AppGlobal::moveForward()
{
    currentPlayListModel->moveForward(repeatMode, randomMode);
}
//------------------------------------------------------------------------------
void AppGlobal::moveBackward()
{
    currentPlayListModel->moveBackward(repeatMode, randomMode);
}
//------------------------------------------------------------------------------
bool AppGlobal::getRepeatMode() const
{
    return repeatMode;
}
//------------------------------------------------------------------------------
bool AppGlobal::getRandomMode() const
{
    return randomMode;
}
//------------------------------------------------------------------------------
void AppGlobal::setCurrentCustomPlayListModel()
{
    currentPlayListModel = customPlayListModel;
    emit sigNewCurrentPlayListModel();
}
//------------------------------------------------------------------------------
PlayListModel* AppGlobal::getCurrentPlayListModel() const
{
    return currentPlayListModel;
}
//------------------------------------------------------------------------------
void AppGlobal::setCurrentAllPlayListModel()
{
    currentPlayListModel = allPlayListModel;
    emit sigNewCurrentPlayListModel();
}
//------------------------------------------------------------------------------
int AppGlobal::getCurrentFileId() const
{
    return currentPlayListModel->getCurrentFileId();
}
//------------------------------------------------------------------------------
void AppGlobal::setCurrentFileId(int value)
{
    currentPlayListModel->setCurrentFileId(value);
}
//------------------------------------------------------------------------------
int AppGlobal::getCurrentFileIndex() const
{
    return currentPlayListModel->getCurrentFileIndex();
}
//------------------------------------------------------------------------------
QString AppGlobal::getRootDirPath() const
{
    return rootDirPath;
}
//------------------------------------------------------------------------------
void AppGlobal::setRootDirPath(const QString &value)
{
    rootDirPath = value;
}
//------------------------------------------------------------------------------
void AppGlobal::scanRootDir()
{
    dataBase->scanRootDir(rootDirPath);
}
//------------------------------------------------------------------------------
AppGlobal* AppGlobal::i()
{
    return inst;
}
//------------------------------------------------------------------------------
UserOptions* AppGlobal::getUserOptions()
{
    return userOptionsInst;
}
//------------------------------------------------------------------------------
QString AppGlobal::getTextValue(const QString &key) const
{
    return textValueInst->getValue(key);
}
//------------------------------------------------------------------------------
database::DataBase* AppGlobal::getDataBase()
{
    return dataBase;
}
//------------------------------------------------------------------------------
AppGlobal::EAppState AppGlobal::getState() const
{
    return state;
}
//------------------------------------------------------------------------------
AppGlobal::EAppState AppGlobal::getPastState() const
{
    return pastState;
}
//------------------------------------------------------------------------------
Options *AppGlobal::getOptions() const
{
    return optionsInst;
}
