#ifndef DIR_H
#define DIR_H

#include <QString>
#include <QList>

#include "record.h"

namespace database {
//==============================================================================

class Dir:public Record
{
public:
  Dir();

  enum EType{
    TypeUnknown = 0,
    TypeRoot = 0x1,
    TypeSubDir = 0x2,

    //TypeHidden = 0x10,
    //TypeVisible = 0x20

  };

  EType type;
  QString name;
  int parentId;
  QString comment;

  Dir* parent;
  QList<Dir*> children ;

};
//==============================================================================
}
#endif // DIR_H
