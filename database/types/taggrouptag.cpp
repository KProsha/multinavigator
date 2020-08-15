#include "taggrouptag.h"

namespace database {
//==============================================================================

TagGroupTag::TagGroupTag()
{

}
//------------------------------------------------------------------------------
quint64 TagGroupTag::getId() const
{
    return id;
}
//------------------------------------------------------------------------------
void TagGroupTag::setId(const quint64& value)
{
    id = value;
}
//------------------------------------------------------------------------------
quint64 TagGroupTag::getTagGroupId() const
{
    return tagGroupId;
}
//------------------------------------------------------------------------------
void TagGroupTag::setTagGroupId(const quint64& value)
{
    tagGroupId = value;
}
//------------------------------------------------------------------------------
quint64 TagGroupTag::getTagId() const
{
    return tagId;
}
//------------------------------------------------------------------------------
void TagGroupTag::setTagId(const quint64& value)
{
    tagId = value;
}
//==============================================================================
}
