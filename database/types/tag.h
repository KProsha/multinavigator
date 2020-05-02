#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QSharedData>

namespace database {
//==============================================================================
class Tag
{
public:
    enum EType{
        TypeAuto  = 0x1,
        TypeUser = 0x2

    };

    int getId() const;
    void setId(int value);

    EType getType() const;
    void setType(const EType& value);

    QString getName() const;
    void setName(const QString& value);

private:
    int id;
    EType  type;
    QString name;
};

//==============================================================================
}


#endif // TAG_H
