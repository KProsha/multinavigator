#include "playlist.h"


namespace database {
//==============================================================================

PlayList::PlayList()
{

}
//------------------------------------------------------------------------------
QString PlayList::getName() const
{
    return name;
}
//------------------------------------------------------------------------------
void PlayList::setName(const QString& value)
{
    name = value;
}
//------------------------------------------------------------------------------
QString PlayList::getComment() const
{
    return comment;
}
//------------------------------------------------------------------------------
void PlayList::setComment(const QString& value)
{
    comment = value;
}
//==============================================================================
}
