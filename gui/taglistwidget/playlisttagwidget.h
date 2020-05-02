#ifndef PLAYLISTTAGWIDGET_H
#define PLAYLISTTAGWIDGET_H

#include <QPushButton>

#include "taglistwidget.h"

class PlayListTagWidget : public TagListWidget
{
    Q_OBJECT
public:
    explicit PlayListTagWidget(QWidget *parent = nullptr);

signals:
    void sigTagSelected(QList<int>);

protected:
    void onTagClickedImpl(int tagId);



//    QPushButton* playListNameEdit;
};

#endif // PLAYLISTTAGWIDGET_H
