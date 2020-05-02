#include "tagwidget.h"

TagWidget::TagWidget(database::Tag& t, QWidget* parent):QWidget(parent)
{       
    tag = t;
}
//------------------------------------------------------------------------------
int TagWidget::getTagId()
{
    return tag.getId();
}
