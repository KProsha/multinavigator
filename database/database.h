#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutexLocker>

#include "filetable.h"
#include "filetagtable.h"
#include "tagtable.h"
#include "dirtable.h"
#include "taggrouptable.h"
#include "taggrouptagtable.h"

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

    void addTag(const QString& name);
    bool renameTag(int tagId, const QString& newName);
    void removeTag(int tagId);
    QList<Tag> getAllTags();
    QList<Tag> getTagList(quint64 tagGroupId);
    QList<Tag> getFileTag(int fileId);

    QList<File> getAllFiles();
    QList<File> getFilesFromDir(int dirId);
    QList<File> getFilesWithTags(QHash<int, database::Tag::ESelectionType> filterTagList);

    QList<TagGroup> getAllTagGroups();
    QList<quint64> getTagGroupsId(quint64 tagGroup);
    void removeTagGroup(int id);
    bool renameTagGroup(int id, const QString& newName);

    void toggleFileTag(int fileId, int tagId);

    void addTagGroup(const QString& name);
    void deleteTagGroup(quint64 id);

    void toggleTagGroupTag(quint64 tagGroupId, quint64 tagId, bool enable);
//    List<quint64> getTagsId(quint64 tagGroupId);

signals:
    void sigTagUpdated();
    void sigDirUpdated();
    void sigFileUpdated();
    void sigFileTagUpdated();
    void sigTagGroupUpdated();
    void sigTagGroupTagUpdated();

protected:
    QString rootDirPath;

    QSqlDatabase sqlDataBase;

    void configDB();
    void searchSubDirs(Dir dir, const QString& absolutePath);
    void searchFiles(Dir dir, const QString& absolutePath);
    void addAutoTags(quint64 autoTagGroupId, quint64 allTagGroupId);
    //-----  -----
    QSharedPointer<FileTable> fileTable;
    QSharedPointer<TagTable> tagTable;
    QSharedPointer<FileTagTable> fileTagTable;
    QSharedPointer<DirTable> dirTable;
    QSharedPointer<TagGroupTable> tagGroupTable;
    QSharedPointer<TagGroupTagTable> tagGroupTagTable;

    friend class TagTable;
    friend class FileTable;
    friend class FileTagTable;
    friend class DirTable;
    friend class TagGroupTable;
    friend class TagGroupTagTable;

    //-----  -----
    Dictionary dictionary;

};
//==============================================================================
}
#endif // DATABASE_H
