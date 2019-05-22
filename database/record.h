#ifndef RECORD_H
#define RECORD_H


class Record
{
public:
  Record();
  virtual ~Record(){};

  bool notInserted(){return (id == -1);}
  int id;
};

#endif // RECORD_H
