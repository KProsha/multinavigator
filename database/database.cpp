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
}
//------------------------------------------------------------------------------
void DataBase::scanRootDir(const QString &name)
{    
    auto dir = dirTable->getRootDir();

    if(!dir.isValid()){

        dir.setType(Dir::TypeRoot);
        dir.setName("root");
        dir.setParentId(-1);
        dirTable->addDirAndGetId(dir);
    }

    searchFiles(dir, name);
    searchSubDirs(dir, name);

    if(AppGlobal::i()->getUserOptions()->getUseFileNameAsTag()){
        addAutoTags();
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
void DataBase::addAutoTags()
{

    auto autoTags = dictionary.getTagAndFileIds(AppGlobal::i()->getUserOptions()->getFileNameCountForTag());

    if(!transaction()) return;

    for(auto it = autoTags.begin(); it != autoTags.end(); ++it) {
        int tagId = tagTable->addTagAndGetId(it.key(), Tag::TypeAuto);
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
void DataBase::addTag(const QString& name, Tag::EType type)
{
    tagTable->addTag(name, type);
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
QList<File> DataBase::getFilesWithTags(QList<int> tagList)
{
    QList<File> res;

    QStringList tagListString;
    foreach (int tag, tagList) {
        tagListString.append(QString::number(tag));
    }

    auto query = sendQuery(QString("SELECT * FROM file WHERE Id "
                                   "IN (SELECT fileId FROM fileTag WHERE fileTag.tagId IN (%1))")
                           .arg(tagListString.join(',')));

    if(query.isNull()) return res;

    while (query->next()) {
        res.append(fileTable->fromSqlQuery(query));
    }

    return res;
}
//------------------------------------------------------------------------------
void DataBase::toggleFileTag(int fileId, int tagId)
{
    fileTagTable->toggleFileTag(fileId, tagId);    
    emit sigFileTagUpdated();
}

//------------------------------------------------------------------------------


//==============================================================================
}















