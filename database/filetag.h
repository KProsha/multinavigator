#ifndef FILETAGDB_H
#define FILETAGDB_H

#include "file.h"
#include "tag.h"
#include "record.h"



namespace database {
//==============================================================================


class FileTag:public Record
{
public:
  FileTag();

  int fileId;
  int tagId;

};
//==============================================================================
}

#endif // FILETAGDB_H
