#ifndef EDITTAGWIDGET_H
#define EDITTAGWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include "gui/widgets/idwidget.h"

class EditTagWidget : public IdWidget<QFrame>
{
    Q_OBJECT
public:
    explicit EditTagWidget(database::Tag& t, QWidget *parent = nullptr);

signals:

protected slots:
    void onRename();
    void onRemove();

    void onTagGroupCheckBox(bool checked);
    void updateTagGroups();

protected:   
    QLabel* nameLabel;
    QHBoxLayout* mainLayout;

    QList<QWidget*> tagGroupWidgets;


};

#endif // EDITTAGWIDGET_H
