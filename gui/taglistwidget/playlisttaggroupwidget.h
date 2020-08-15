#ifndef PLAYLISTTAGGROUPWIDGET_H
#define PLAYLISTTAGGROUPWIDGET_H

#include <QPushButton>

#include "taglistgroupwidget.h"

class PlayListTagGroupWidget : public TagListGroupWidget
{
    Q_OBJECT
public:
    explicit PlayListTagGroupWidget(database::TagGroup tGroup, QWidget *parent = nullptr);

protected:
    void addTagWidget(database::Tag tag) override;



//    QPushButton* playListNameEdit;
};

#endif // PLAYLISTTAGGROUPWIDGET_H
