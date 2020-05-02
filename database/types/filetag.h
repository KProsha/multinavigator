#ifndef FILETAGDB_H
#define FILETAGDB_H

#include <QSharedData>

namespace database {
//==============================================================================

class FileTag
{
public:
    FileTag();

    int getId() const;
    void setId(int value);

    int getFileId() const;
    void setFileId(int value);

    int getTagId() const;
    void setTagId(int value);

    bool getEnable() const;
    void setEnable(bool value);

protected:
    int id;
    int fileId;
    int tagId;
    bool enable;

};
//==============================================================================
}

#endif // FILETAGDB_H
