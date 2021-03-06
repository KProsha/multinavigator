#include "taggroup.h"

namespace database {
//==============================================================================


TagGroup::TagGroup()
{

}
//------------------------------------------------------------------------------
quint64 TagGroup::getId() const
{
    return id;
}
//------------------------------------------------------------------------------

void TagGroup::setId(quint64 value)
{
    id = value;
}
//------------------------------------------------------------------------------

QString TagGroup::getName() const
{
    return name;
}
//------------------------------------------------------------------------------
void TagGroup::setName(const QString& value)
{
    name = value;
}
//==============================================================================
}
