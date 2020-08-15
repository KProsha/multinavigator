#ifndef EDITTAGGROUPLISTWIDGET_H
#define EDITTAGGROUPLISTWIDGET_H

#include "gui/widgets/listviewwidget.h"
#include "database/types/taggroup.h"

class EditTagGroupListWidget : public ListViewWidget
{
    Q_OBJECT
public:
    explicit EditTagGroupListWidget(QWidget *parent = nullptr);

protected slots:
    void updateAvaliableTagGroup();
};




#endif // EDITTAGGROUPLISTWIDGET_H
