#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <QString>
#include <QDateTime>


#include "dir.h"
#include "record.h"


namespace database {
//==============================================================================

class File:public Record
{
public:
  File();

  QDateTime created;
  QDateTime lastModified;
  QDateTime registered;
  QString type;
  QString name;
  qint64 size;
  int dirId;
  QString comment;

};
//==============================================================================
}

#endif // MEDIAFILE_H
