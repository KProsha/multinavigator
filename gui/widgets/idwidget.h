#ifndef IDGWIDGET_H
#define IDGWIDGET_H

#include <QPushButton>
#include "database/types/tag.h"

template <class TWidget>
class IdWidget: public TWidget
{    
public:
    IdWidget(quint64 id, QWidget* parent):TWidget(parent){
        _id = id;
    }

    int getId(){
        return _id;
    }
protected:
    quint64 _id;
};

#endif // IDGWIDGET_H
