#ifndef EDITTAGLISTWIDGET_H
#define EDITTAGLISTWIDGET_H

#include "taglistwidget.h"

class EditTagListWidget : public TagListWidget
{
    Q_OBJECT
public:
    explicit EditTagListWidget(QWidget *parent = nullptr);

protected:
    void addTagWidget(database::Tag tag) override;
};




#endif // EDITTAGLISTWIDGET_H
