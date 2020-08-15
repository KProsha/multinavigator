#ifndef TAGGROUPTAG_H
#define TAGGROUPTAG_H

#include <qglobal.h>

namespace database {
//==============================================================================

class TagGroupTag
{
public:
    TagGroupTag();

    quint64 getId() const;
    void setId(const quint64& value);

    quint64 getTagGroupId() const;
    void setTagGroupId(const quint64& value);

    quint64 getTagId() const;
    void setTagId(const quint64& value);

private:
    quint64 id;
    quint64 tagGroupId;
    quint64 tagId;

};
//==============================================================================
}

#endif // TAGGROUPTAG_H
