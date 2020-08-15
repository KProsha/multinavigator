#ifndef EDITTAGLISTWIDGET_H
#define EDITTAGLISTWIDGET_H

#include "gui/widgets/listviewwidget.h"

class EditTagListWidget : public ListViewWidget
{
    Q_OBJECT
public:
    explicit EditTagListWidget(QWidget *parent = nullptr);

protected slots:
    void updateAvaliableTag();


protected:
    void addTagWidget(database::Tag tag);
    void updateAvaliableTagImpl();
};




#endif // EDITTAGLISTWIDGET_H
