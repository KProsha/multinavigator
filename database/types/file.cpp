
#include "file.h"

namespace database {
//==============================================================================
File::File()
{
    d = new FileData;
}
//------------------------------------------------------------------------------
QString File::getComment() const
{
    return d->comment;
}
//------------------------------------------------------------------------------
void File::setComment(const QString& value)
{
    d->comment = value;
}
//------------------------------------------------------------------------------
int File::getDirId() const
{
    return d->dirId;
}
//------------------------------------------------------------------------------
void File::setDirId(int value)
{
    d->dirId = value;
}
//------------------------------------------------------------------------------
qint64 File::getSize() const
{
    return d->size;
}
//------------------------------------------------------------------------------
void File::setSize(const qint64& value)
{
    d->size = value;
}
//------------------------------------------------------------------------------
QString File::getName() const
{
    return d->name;
}
//------------------------------------------------------------------------------
void File::setName(const QString& value)
{
    d->name = value;
}
//------------------------------------------------------------------------------
QString File::getType() const
{
    return d->type;
}
//------------------------------------------------------------------------------
void File::setType(const QString& value)
{
    d->type = value;
}
//------------------------------------------------------------------------------
QDateTime File::getCreated() const
{
    return d->created;
}
//------------------------------------------------------------------------------
void File::setCreated(const QDateTime& value)
{
    d->created = value;
}
//------------------------------------------------------------------------------
int File::getId() const
{
    return d->id;
}
//------------------------------------------------------------------------------
void File::setId(int value)
{
    d->id = value;
}
//------------------------------------------------------------------------------
FileData::FileData()
{

}
//------------------------------------------------------------------------------
FileData::FileData(const FileData& other):
        QSharedData(other),
        id(other.id),
        created(other.created),
        type(other.type),
        name(other.name),
        size(other.size),
        dirId(other.dirId),
        comment(other.comment)
{

}


//==============================================================================
}
