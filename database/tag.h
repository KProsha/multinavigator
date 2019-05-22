#ifndef TAG_H
#define TAG_H

#include <QString>
#include "record.h"


namespace database {
//==============================================================================



class Tag:public Record
{
public:
  Tag();

  enum EType{
    TypeDir  = 1,
    TypeUser = 2

  };

  EType  type;
  QString name;
  QString comment;

};

//==============================================================================
}


#endif // TAG_H
