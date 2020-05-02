#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QPushButton>
#include "database/types/tag.h"

class TagWidget: public QWidget
{    
public:
    TagWidget(database::Tag& t, QWidget* parent);

    int getTagId();
protected:
    database::Tag tag;
};

#endif // TAGWIDGET_H
