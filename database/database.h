#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutexLocker>

#include "filetable.h"
#include "filetagtable.h"
#include "tagtable.h"
#include "dirtable.h"

#include "backend/dictionary.h"

namespace database {
//==============================================================================

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    // -----  -----
    static DataBase* i;
    // -----  -----
    bool connect();
    void disconnect();

    QSharedPointer<QSqlQuery> query();
    QSharedPointer<QSqlQuery> sendQuery(const QString& queryText);
    bool transaction();
    bool rollback();
    bool commit();
    // -----  -----
    bool openDir(const QString& name);
    void scanRootDir(const QString& name);
    // -----  -----
    QString getFilePath(int fileId);
    QString getDirRelativePath(int dirId);

    void addTag(const QString& name, Tag::EType type);
    bool renameTag(int tagId, const QString& newName);
    void removeTag(int tagId);
    QList<Tag> getAllTags();
    QList<Tag> getFileTag(int fileId);

    QList<File> getAllFiles();
    QList<File> getFilesFromDir(int dirId);
    QList<File> getFilesWithTags(QList<int> tagList);

    void toggleFileTag(int fileId, int tagId);
signals:
    void sigTagUpdated();
    void sigDirUpdated();
    void sigFileUpdated();
    void sigFileTagUpdated();


protected:
    QString rootDirPath;

    QSqlDatabase sqlDataBase;
    QMutex* databaseMutex;

    void configDB();
    void searchSubDirs(Dir dir, const QString& absolutePath);
    void searchFiles(Dir dir, const QString& absolutePath);
    void addAutoTags();
    //-----  -----
    QSharedPointer<FileTable> fileTable;
    QSharedPointer<TagTable> tagTable;
    QSharedPointer<FileTagTable> fileTagTable;
    QSharedPointer<DirTable> dirTable;

    friend class TagTable;
    friend class FileTable;
    friend class FileTagTable;
    friend class DirTable;
    //-----  -----
    Dictionary dictionary;

};
//==============================================================================
}
#endif // DATABASE_H
