#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QSharedData>

namespace database {
//==============================================================================
class Tag
{
public:
    enum ESelectionType{
        TypeAnd,
        TypeOr,
        TypeNot,
        NotSelected
    };

    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString& value);

    ESelectionType getSelectionType() const;
    void setSelectionType(const ESelectionType& value);

private:
    int id;
    QString name;

    ESelectionType selectionType; // not database

};

//==============================================================================
}


#endif // TAG_H
