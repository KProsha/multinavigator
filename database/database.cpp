#include "database.h"

#include <QSqlQuery>
#include <QDir>
#include <QSqlError>
#include <QFileInfo>

#include "options/options.h"
#include "backend/appglobal.h"

namespace database {
//==============================================================================
DataBase* DataBase::i = nullptr;

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    fileTable = QSharedPointer<FileTable>(new FileTable(this));
    tagTable = QSharedPointer<TagTable>(new TagTable(this));
    fileTagTable = QSharedPointer<FileTagTable>(new FileTagTable(this));
    dirTable = QSharedPointer<DirTable>(new DirTable(this));
    tagGroupTable = QSharedPointer<TagGroupTable>(new TagGroupTable(this));
    tagGroupTagTable = QSharedPointer<TagGroupTagTable>(new TagGroupTagTable(this));

    i = this;
}
//------------------------------------------------------------------------------
DataBase::~DataBase()
{  
    sqlDataBase.close();
}
//------------------------------------------------------------------------------
bool DataBase::openDir(const QString& path)
{
    sqlDataBase.close();
    sqlDataBase.removeDatabase(rootDirPath);

    rootDirPath = path;
    bool ok = connect();
    if(!ok) return false;

    emit sigTagUpdated();
    emit sigDirUpdated();
    emit sigFileUpdated();
    emit sigFileTagUpdated();
    emit sigTagGroupUpdated();

    return true;
}
//------------------------------------------------------------------------------
bool DataBase::connect()
{
    if(sqlDataBase.isOpen()) return true;

    if(!sqlDataBase.isValid())
    {
        if(rootDirPath.isEmpty()) return false;

        QFileInfo dataBaseFileInfo(rootDirPath, AppGlobal::i()->getOptions()->getDatabaseFileName());

        sqlDataBase = QSqlDatabase::addDatabase("QSQLITE",rootDirPath);
        sqlDataBase.setDatabaseName(dataBaseFileInfo.absoluteFilePath());        
    }

    bool ok = sqlDataBase.open();

    if(ok){        

        QSqlQuery query(sqlDataBase);
        query.exec("PRAGMA encoding = \"UTF-8\";");

        query.clear();

        configDB();
        //    query.exec("PRAGMA journal_mode = WAL");
    }

    return ok;
}
//------------------------------------------------------------------------------
void DataBase::disconnect()
{
    sqlDataBase.close();
}
//------------------------------------------------------------------------------
QSharedPointer<QSqlQuery> DataBase::query()
{
    return QSharedPointer<QSqlQuery>(new QSqlQuery(sqlDataBase));
}
//------------------------------------------------------------------------------
QSharedPointer<QSqlQuery> DataBase::sendQuery(const QString &queryText)
{
    QSharedPointer<QSqlQuery> query =  QSharedPointer<QSqlQuery>(new QSqlQuery(sqlDataBase));

    if(!query->exec(queryText)){
        qDebug() << "Sql query: '" << query->lastQuery() << "' error:" << query->lastError().text();
    }

    return query;
}
//------------------------------------------------------------------------------
bool DataBase::transaction()
{
    return sqlDataBase.transaction();
}
//------------------------------------------------------------------------------
bool DataBase::rollback()
{
    return sqlDataBase.rollback();
}
//------------------------------------------------------------------------------
bool DataBase::commit()
{
    return sqlDataBase.commit();
}
//------------------------------------------------------------------------------
void DataBase::configDB()
{
    QStringList tables = sqlDataBase.tables();

    if (!tables.contains("file")) fileTable->createTable();
    if (!tables.contains("tag"))  tagTable->createTable();
    if (!tables.contains("fileTag")) fileTagTable->createTable();
    if (!tables.contains("directory"))  dirTable->createTable();
    if (!tables.contains("taggroup"))  tagGroupTable->createTable();
    if (!tables.contains("taggrouptag"))  tagGroupTagTable->createTable();
}
//------------------------------------------------------------------------------
void DataBase::scanRootDir(const QString &name)
{    
    auto dir = dirTable->getRootDir();

    if(!dir.isValid()){

        dir.setType(Dir::TypeRoot);
        dir.setName("root");
        dir.setParentId(-1);
        int dirId = dirTable->addDirAndGetId(dir);

    }

    searchFiles(dir, name);
    searchSubDirs(dir, name);

    if(AppGlobal::i()->getUserOptions()->getUseFileNameAsTag()){
        int autoTagGroupId = tagGroupTable->addGroupAndGetId(AppGlobal::i()->getTextValue("tag/AutoTagGroup"));
        int allTagGroupId = tagGroupTable->addGroupAndGetId(AppGlobal::i()->getTextValue("tag/AllTagGroup"));
        addAutoTags(autoTagGroupId, allTagGroupId);
        emit sigTagUpdated();
    }

    emit sigFileUpdated();
}
//------------------------------------------------------------------------------
void DataBase::searchSubDirs(database::Dir dir, const QString& absolutePath)
{
    //-----  -----
    QDir dirQt(absolutePath);
    QStringList dirEntryList = dirQt.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    foreach (QString dirEntry, dirEntryList) {
        Dir subDir;

        subDir.setType(Dir::TypeSubDir);
        subDir.setName(dirEntry);
        subDir.setParentId(dir.getId());
        subDir.setRelativePath(QDir::toNativeSeparators(dir.getRelativePath() +"/" + subDir.getName()));
        int id = dirTable->getId(subDir.getRelativePath());

        if(id < 0)
            dirTable->addDirAndGetId(subDir);
        else
            subDir.setId(id);

        QString subDirAbsolutePath = QDir::toNativeSeparators(absolutePath + "/" + dirEntry);

        searchFiles(subDir, subDirAbsolutePath);
        searchSubDirs(subDir, subDirAbsolutePath);
    };
}
//------------------------------------------------------------------------------
void DataBase::searchFiles(Dir dir, const QString& absolutePath)
{
    if(!transaction()) return;
    QDir dirQt(absolutePath);

    foreach (QFileInfo info, dirQt.entryInfoList(AppGlobal::i()->getOptions()->getSuffixList(),
                                                    QDir::Files | QDir::NoDotAndDotDot)) {
        File file;
        file.setCreated(info.created());
        file.setType(info.suffix());
        file.setName(info.completeBaseName());
        file.setSize(info.size());
        file.setDirId(dir.getId());

        fileTable->addFileAndGetId(file);

        if(AppGlobal::i()->getUserOptions()->getUseFileNameAsTag())
            dictionary.addEntry(file.getName(), file.getId(), true);

        if(AppGlobal::i()->getUserOptions()->getUseDirNameAsTag())
            dictionary.addEntry(dir.getName(), file.getId(), false);

    }
    commit();
}
//------------------------------------------------------------------------------
void DataBase::addAutoTags(quint64 autoTagGroupId, quint64 allTagGroupId)
{
    auto autoTags = dictionary.getTagAndFileIds(AppGlobal::i()->getUserOptions()->getFileNameCountForTag());

    if(!transaction()) return;

    for(auto it = autoTags.begin(); it != autoTags.end(); ++it) {
        int tagId = tagTable->addTagAndGetId(it.key());
        tagGroupTagTable->toggleTagGroupTag(autoTagGroupId, tagId);
        tagGroupTagTable->toggleTagGroupTag(allTagGroupId, tagId);

        foreach(int fileId, it.value()){
            fileTagTable->addFileTag(fileId, tagId);
        }
    }
    commit();
}
//------------------------------------------------------------------------------
QString DataBase::getFilePath(int fileId)
{
    auto file = fileTable->getFile(fileId);

    QString dirPath = getDirRelativePath(file.getDirId());
    QString filePath;
    if(dirPath.isEmpty()){
        filePath = QString("%1/%3.%4").arg(rootDirPath).arg(file.getName()).arg(file.getType());
    }else{
        filePath = QString("%1%2/%3.%4").arg(rootDirPath).arg(dirPath).arg(file.getName()).arg(file.getType());
    }

    return filePath;
}
//------------------------------------------------------------------------------
QString DataBase::getDirRelativePath(int dirId)
{   
    Dir dir = dirTable->getDir(dirId);
    if(!dir.isValid()) return "";

    return dir.getRelativePath();
}
//------------------------------------------------------------------------------
QList<database::Tag> database::DataBase::getAllTags()
{
    return  tagTable->getAllTags();
}
//------------------------------------------------------------------------------
QList<Tag> DataBase::getTagList(quint64 tagGroupId)
{
    QList<Tag> res;
    auto query = sendQuery(QString("SELECT * FROM tag WHERE Id "
                                   "IN (SELECT tagId FROM taggrouptag WHERE taggrouptag.tagGroupId=%1 AND taggrouptag.enable <> 0)")
                           .arg(tagGroupId));
    if(query.isNull()) return res;

    while (query->next()) {
        res.append(tagTable->fromSqlQuery(query));
    }
    return res;
}
//------------------------------------------------------------------------------
void DataBase::addTag(const QString& name)
{
    int tagId = tagTable->addTagAndGetId(name);
    int allTagGroupId = tagGroupTable->addGroupAndGetId(AppGlobal::i()->getTextValue("tag/AllTagGroup"));

    tagGroupTagTable->toggleTagGroupTag(allTagGroupId, tagId);

    emit sigTagUpdated();
}
//------------------------------------------------------------------------------
bool DataBase::renameTag(int tagId, const QString& newName)
{
    bool ok = tagTable->renameTag(tagId, newName);
    if(ok) emit sigTagUpdated();
    return ok;
}
//------------------------------------------------------------------------------
void DataBase::removeTag(int tagId)
{
    fileTagTable->deleteRecord(tagId);
    tagTable->deleteTag(tagId);
    tagGroupTagTable->deleteTagGroupTagByTag(tagId);

    emit sigTagUpdated();
}
//------------------------------------------------------------------------------
QList<database::Tag> DataBase::getFileTag(int fileId)
{
    QList<Tag> res;
    auto query = sendQuery(QString("SELECT * FROM tag WHERE Id "
                                   "IN (SELECT tagId FROM fileTag WHERE fileTag.fileId=%1 AND fileTag.enable <> 0)")
                           .arg(fileId));
    if(query.isNull()) return res;

    while (query->next()) {
        res.append(tagTable->fromSqlQuery(query));
    }
    return res;
}
//------------------------------------------------------------------------------
QList<File> DataBase::getAllFiles()
{
    return fileTable->getAllFiles();
}
//------------------------------------------------------------------------------
QList<File> DataBase::getFilesFromDir(int dirId)
{
    QList<File> res;
    auto query = sendQuery(QString("SELECT * FROM file Where DirId=%1)")
                           .arg(dirId));
    if(query.isNull()) return res;

    while (query->next()) {
        res.append(fileTable->fromSqlQuery(query));
    }
    return res;
}
//------------------------------------------------------------------------------
QList<File> DataBase::getFilesWithTags(QHash<int, database::Tag::ESelectionType> filterTagList)
{
    QList<File> res;

    auto getFileId = [this](QList<int> tagIdList) -> QSet<quint64> {
        QSet<quint64> resFileId;
        if(tagIdList.isEmpty()) return resFileId;

        QStringList tagIdStringList;
        foreach (int id, tagIdList) {
            tagIdStringList.append(QString::number(id));
        }

        auto query = sendQuery(QString("SELECT fileId FROM fileTag WHERE fileTag.tagId IN (%1)")
                               .arg(tagIdStringList.join(',')));
        bool ok;
        while (query->next()) {
            quint64 fileId = query->value(0).toULongLong(&ok);
            if(ok) resFileId.insert(fileId);
        }
        return resFileId;
    };

    QSet<quint64> andSet = getFileId(filterTagList.keys(database::Tag::TypeAnd));
    QSet<quint64> orSet  = getFileId(filterTagList.keys(database::Tag::TypeOr));
    QSet<quint64> notSet = getFileId(filterTagList.keys(database::Tag::TypeNot));

    QSet<quint64> fileSet = orSet;
    if(!andSet.isEmpty()) fileSet = fileSet.intersect(andSet);
    if(!notSet.isEmpty()) fileSet = fileSet.subtract(notSet);

    res = fileTable->getFileList(fileSet.toList());

    return res;
}
//------------------------------------------------------------------------------
QList<TagGroup> DataBase::getAllTagGroups()
{
    return tagGroupTable->getAllTagGroupList();
}
//------------------------------------------------------------------------------
QList<quint64> DataBase::getTagGroupsId(quint64 tagGroup)
{
    return tagGroupTagTable->getTagGroupsId(tagGroup);
}
//------------------------------------------------------------------------------
void DataBase::removeTagGroup(int id)
{
    tagGroupTable->deleteGroup(id);
    tagGroupTagTable->deleteTagGroupTagByTag(id);

    emit sigTagGroupUpdated();
}
//------------------------------------------------------------------------------
bool DataBase::renameTagGroup(int id, const QString& newName)
{
    tagGroupTable->rename(id, newName);
    emit sigTagGroupUpdated();
    return true;
}
//------------------------------------------------------------------------------
void DataBase::toggleFileTag(int fileId, int tagId)
{
    fileTagTable->toggleFileTag(fileId, tagId);    
    emit sigFileTagUpdated();
}
//------------------------------------------------------------------------------
void DataBase::addTagGroup(const QString& name)
{
    tagGroupTable->addGroup(name);
    emit sigTagGroupUpdated();
}
//------------------------------------------------------------------------------
void DataBase::deleteTagGroup(quint64 id)
{
    tagGroupTable->deleteGroup(id);    
    emit sigTagGroupUpdated();
}
//------------------------------------------------------------------------------
void DataBase::toggleTagGroupTag(quint64 tagGroupId, quint64 tagId, bool enable)
{
    tagGroupTagTable->toggleTagGroupTag(tagGroupId, tagId, enable);
    emit sigTagGroupTagUpdated();
}
//------------------------------------------------------------------------------
//List<quint64> DataBase::getTagsId(quint64 tagGroupId)
//{
//    return ;
//}
//------------------------------------------------------------------------------


//==============================================================================
}















