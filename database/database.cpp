#include "database.h"

#include <QSqlQuery>
#include <QDir>

#include "options/options.h"

#include <QDebug>
namespace database {
//==============================================================================
DataBase* DataBase::i = nullptr;

DataBase::DataBase(QObject *parent) : QObject(parent)
{
  databaseMutex = new QMutex(QMutex::Recursive);

  fileTable = QSharedPointer<FileTable>(new FileTable());
  tagTable = QSharedPointer<TagTable>(new TagTable());
  fileTagTable = QSharedPointer<FileTagTable>(new FileTagTable());
  dirTable = QSharedPointer<DirTable>(new DirTable());

  i = this;
}
//------------------------------------------------------------------------------
DataBase::~DataBase()
{  
  disconnect();
}
//------------------------------------------------------------------------------
bool DataBase::openDir(const QString& name)
{
  disconnect();

  dirName = name;
  return  connect();
}
//------------------------------------------------------------------------------
bool DataBase::connect()
{

  if(sqlDataBbase.isOpen()) return true;

  if(!sqlDataBbase.isValid())
  {
    if(dirName.isEmpty()) return false;

    QFileInfo dataBaseFileInfo(dirName, Options::i->databaseFileName);

    sqlDataBbase = QSqlDatabase::addDatabase("QSQLITE");
    sqlDataBbase.setDatabaseName(dataBaseFileInfo.absoluteFilePath());

    configDB();
  }

  bool ok = sqlDataBbase.open();

  if(ok){

    QSqlQuery query(sqlDataBbase);
    query.exec("PRAGMA encoding = \"UTF-8\";");

    query.clear();
    query.exec("PRAGMA journal_mode = WAL");
  }

  return ok;
}
//------------------------------------------------------------------------------
void DataBase::disconnect()
{   
  QMutexLocker L(databaseMutex);
  sqlDataBbase.close();
}

//--------------------------------------------------------------
void DataBase::configDB()
{
  QStringList tables = sqlDataBbase.tables();

  if (!tables.contains(fileTable->name)) fileTable->createTable();
  if (!tables.contains(tagTable->name)) tagTable->createTable();
  if (!tables.contains(fileTagTable->name)) fileTagTable->createTable();
  if (!tables.contains(dirTable->name)) dirTable->createTable();
}
//------------------------------------------------------------------------------
void DataBase::addRootDir(const QString &name)
{
  QMutexLocker L(databaseMutex);

  int Id = scanSubDir(name);

  emit sigDirUpdateEvent(Id);
}
//------------------------------------------------------------------------------
int DataBase::scanSubDir(const QString &name, const QString &parendDirPath, int parentDirId)
{
  //-----  -----
  Dir::EType dirType;
  QString dirName;
  if(parentDirId != -1){
    dirType = Dir::TypeSubDir;
    dirName = name;
  }else {
    dirType = Dir::TypeRoot;
    dirName = "root";
  }


  auto getUniqueDir = [&]() -> QSharedPointer<Dir> {
    auto dirList = dirTable->getDirList(dirName);
    foreach (auto dirNamed, dirList) {
      if(dirNamed->parentId == parentDirId) return dirNamed;
    }
    return QSharedPointer<Dir>(nullptr);
  };

  auto dir = getUniqueDir();

  if(dir.isNull()){
      dir = dirTable->addDir(dirType,
                             dirName,
                             parentDirId);
//      auto tag = tagTable->addTag(dir->name,Tag::TypeDir);
  }

  QDir dirQt;
  if(parentDirId != -1)
    dirQt.setPath(QDir::toNativeSeparators(parendDirPath +"/" + name));
  else
    dirQt.setPath(name);
  //-----  -----
  QStringList FileEntryList = dirQt.entryList(QDir::Files | QDir::NoDotAndDotDot);

  foreach (QString Entry, FileEntryList) {

    QFileInfo info(QDir::toNativeSeparators(dirQt.absolutePath() +"/" + Entry));

    if(!Options::i->suffixList.contains(info.suffix()))continue;


    auto isUniqueFile = [&]() -> bool{
        auto fileList = fileTable->getFileList(info.fileName());
        foreach (auto fileNamed, fileList) {
            if(fileNamed->dirId == dir->id) return false;
        }
        return true;
    };

    if(isUniqueFile() == false) continue;

    fileTable->addFile(info.created(),
                       info.lastModified(),
                       QDateTime::currentDateTime(),
                       info.suffix(),
                       info.completeBaseName(),
                       info.size(),
                       dir->id
                       );

  };
  //-----  -----

  QStringList dirEntryList = dirQt.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

  foreach (QString entry, dirEntryList) {
    scanSubDir(entry,
              dirQt.absolutePath(),
              dir->id
              );
  };
  return dir->id;

}

//==============================================================================
}















