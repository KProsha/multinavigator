#ifndef EDITTAGWIDGET_H
#define EDITTAGWIDGET_H

#include "tagwidget.h"

class EditTagWidget : public TagWidget
{
    Q_OBJECT
public:
    explicit EditTagWidget(database::Tag& t, QWidget *parent = nullptr);

signals:

protected slots:
    void onRename();
    void onRemove();

protected:
    int tagId;
};

#endif // EDITTAGWIDGET_H
