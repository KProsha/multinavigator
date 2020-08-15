#ifndef EDITTAGGROUPWIDGET_H
#define EDITTAGGROUPWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include "gui/widgets/idwidget.h"
#include "database/types/taggroup.h"


class EditTagGroupWidget : public IdWidget<QFrame>
{
    Q_OBJECT
public:
    explicit EditTagGroupWidget(database::TagGroup& t, QWidget *parent = nullptr);

signals:

protected slots:
    void onRename();
    void onRemove();

    void onTagGroupCheckBox(bool checked);


protected:   
    QLabel* nameLabel;
    QHBoxLayout* mainLayout;
};

#endif // EDITTAGGROUPWIDGET_H
