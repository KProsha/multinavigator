#ifndef TAGLISTGROUPWIDGET_H
#define TAGLISTGROUPWIDGET_H

#include <QVBoxLayout>
#include <QGroupBox>

#include "gui/widgets/idwidget.h"
#include <database/types/taggroup.h>

class TagListGroupWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit TagListGroupWidget(database::TagGroup tGroup, QWidget *parent = nullptr);

public slots:
    void updateAvaliableTag();
    void minimizeMaximize();

protected:
    database::TagGroup tagGroup;

    QVBoxLayout* tagLayout;
    QList<IdWidget<QFrame>*> tagWidgetList;

    virtual void addTagWidget(database::Tag tag) = 0;    


};

#endif //
