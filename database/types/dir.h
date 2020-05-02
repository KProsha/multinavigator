#ifndef DIR_H
#define DIR_H

#include <QString>
#include <QSharedData>

namespace database {
//==============================================================================

class DirData;

class Dir
{
public:    
    Dir();

    enum EType{        
        TypeUnknown = 0,
        TypeRoot = 0x1,
        TypeSubDir = 0x2
    };
    bool isValid();

    int getId() const;
    void setId(int value);

    Dir::EType getType() const;
    void setType(const Dir::EType& value);

    QString getName() const;
    void setName(const QString& value);

    QString getRelativePath() const;
    void setRelativePath(const QString& value);

    int getParentId() const;
    void setParentId(int value);

private:
    QSharedDataPointer<DirData> d;

};
//------------------------------------------------------------------------------
class DirData: public QSharedData
{
public:
    DirData();
    DirData (const DirData& other);

    int id;
    Dir::EType type;
    QString name;
    QString relativePath;
    int parentId;
};


//==============================================================================
}
#endif // DIR_H
