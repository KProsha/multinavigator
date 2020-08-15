#ifndef FILETAGGROUPWIDGET_H
#define FILETAGGROUPWIDGET_H

#include "taglistgroupwidget.h"
#include "database/types/taggroup.h"

class FileTagGroupWidget : public TagListGroupWidget
{
    Q_OBJECT
public:
    explicit FileTagGroupWidget(database::TagGroup tGroup, QWidget *parent = nullptr);

protected slots:
    void updateFileTag();
    void onTagClicked(int tagId);

protected:
    void addTagWidget(database::Tag tag) override;
};

#endif // FILETAGGROUPWIDGET_H
