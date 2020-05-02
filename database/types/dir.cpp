
#include "dir.h"


namespace database {
//==============================================================================
Dir::Dir()
{
    d = new DirData;
}
//------------------------------------------------------------------------------
bool Dir::isValid()
{
    return d->type != Dir::TypeUnknown;
}
//------------------------------------------------------------------------------
int Dir::getParentId() const
{
    return d->parentId;
}
//------------------------------------------------------------------------------
void Dir::setParentId(int value)
{
    d->parentId = value;
}
//------------------------------------------------------------------------------
QString Dir::getRelativePath() const
{
    return d->relativePath;
}
//------------------------------------------------------------------------------
void Dir::setRelativePath(const QString& value)
{
    d->relativePath = value;
}
//------------------------------------------------------------------------------
QString Dir::getName() const
{
    return d->name;
}
//------------------------------------------------------------------------------
void Dir::setName(const QString& value)
{
    d->name = value;
}
//------------------------------------------------------------------------------
Dir::EType Dir::getType() const
{
    return d->type;
}
//------------------------------------------------------------------------------
void Dir::setType(const Dir::EType& value)
{
    d->type = value;
}
//------------------------------------------------------------------------------
int Dir::getId() const
{
    return d->id;
}
//------------------------------------------------------------------------------
void Dir::setId(int value)
{
    d->id = value;
}
//==============================================================================
DirData::DirData()
{
    type = Dir::TypeUnknown;
}
//------------------------------------------------------------------------------
DirData::DirData(const DirData& other):
    QSharedData(other),
    id(other.id),
    type(other.type),
    name(other.name),
    relativePath(other.relativePath),
    parentId(other.parentId)
{

}

//------------------------------------------------------------------------------



//==============================================================================
}
