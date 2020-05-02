#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <QString>
#include <QDateTime>
#include <QSharedData>

namespace database {
//==============================================================================
class FileData;


class File
{
public:
    File();

    int getId() const;
    void setId(int value);

    QDateTime getCreated() const;
    void setCreated(const QDateTime& value);

    QString getType() const;
    void setType(const QString& value);

    QString getName() const;
    void setName(const QString& value);

    qint64 getSize() const;
    void setSize(const qint64& value);

    int getDirId() const;
    void setDirId(int value);

    QString getComment() const;
    void setComment(const QString& value);

private:
    QSharedDataPointer<FileData> d;
};
//------------------------------------------------------------------------------
class FileData:public QSharedData
{
public:
    FileData();
    FileData(const FileData& other);

    int id;
    QDateTime created;
    QString type;
    QString name;
    qint64 size;
    int dirId;
    QString comment;
};
//==============================================================================
}

#endif // MEDIAFILE_H
