#ifndef TAGGROUP_H
#define TAGGROUP_H

#include <QString>

namespace database {
//==============================================================================

class TagGroup
{
public:
    TagGroup();

    quint64 getId() const;
    void setId(quint64 value);

    QString getName() const;
    void setName(const QString& value);

private:
    quint64 id;
    QString name;
};
//==============================================================================
}
#endif // TAGGROUP_H
