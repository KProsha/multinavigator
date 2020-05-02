#include "playlistmodel.h"

#include "backend/appglobal.h"

PlayListModel::PlayListModel(QObject *parent) : QAbstractTableModel(parent)
{    
    currentFileId = -1;
}
//------------------------------------------------------------------------------
int PlayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return fileList.count();
}
//------------------------------------------------------------------------------
int PlayListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}
//------------------------------------------------------------------------------
QVariant PlayListModel::data(const QModelIndex &index, int role) const
{
    auto file = fileList.at(index.row());

    switch (role) {
    case Qt::DisplayRole:{
        switch (index.column()) {
        case 0: return file.getName();
        case 1: return file.getType();
        case 2: return AppGlobal::i()->getDataBase()->getDirRelativePath(file.getDirId());
        }
    }break;
    case Qt::UserRole:
        return file.getId();
    }
    return QVariant();
}
//------------------------------------------------------------------------------
QVariant PlayListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation==Qt::Vertical){
        return section;
    }

    switch (role) {
    case Qt::DisplayRole:{
        switch (section) {
        case 0: return AppGlobal::i()->getTextValue("playlist/FileName");
        case 1: return AppGlobal::i()->getTextValue("playlist/FileType");
        case 2: return AppGlobal::i()->getTextValue("playlist/Path");

        }
    }
    }
    return QVariant();
}
//------------------------------------------------------------------------------
void PlayListModel::updatePlaylist()
{
    beginResetModel();

    if(filterTagIdList.isEmpty())
        fileList = AppGlobal::i()->getDataBase()->getAllFiles();
    else
        fileList = AppGlobal::i()->getDataBase()->getFilesWithTags(filterTagIdList);

    endResetModel();
}
//------------------------------------------------------------------------------
int PlayListModel::searchFileIndex(int fileId) const
{
    for(int i = 0; i < fileList.count(); ++i){
        if(fileList.at(i).getId() == fileId) return i;
    }
    return -1;
}
//------------------------------------------------------------------------------
int PlayListModel::getCurrentFileId() const
{
    return currentFileId;
}
//------------------------------------------------------------------------------
void PlayListModel::setCurrentFileId(int value)
{
    currentFileId = value;
    emit sigNewCurrentFile();
}
//------------------------------------------------------------------------------
int PlayListModel::getCurrentFileIndex() const
{
    return searchFileIndex(currentFileId);
}
//------------------------------------------------------------------------------
void PlayListModel::setFilterTagIdList(const QList<int>& value)
{
    filterTagIdList = value;
    updatePlaylist();
}
//------------------------------------------------------------------------------
void PlayListModel::moveForward(bool repeat, bool random)
{    
    if(random){
        setCurrentFileId(fileList.at(qrand() % fileList.size()).getId());
    }else{
        int index = getCurrentFileIndex();
        if(index < fileList.count() - 1){
            setCurrentFileId(fileList.at(index + 1).getId());
        }else{
            setCurrentFileId(fileList.first().getId());
        }
    }
}
//------------------------------------------------------------------------------
void PlayListModel::moveBackward(bool repeat, bool random)
{
    int index = getCurrentFileIndex();
    if(index > 0){
        setCurrentFileId(fileList.at(index - 1).getId());
    }else{
        setCurrentFileId(fileList.last().getId());
    }
}
