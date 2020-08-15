#include "playlisttaggroupwidget.h"

#include "backend/appglobal.h"
#include "gui/tagwidget/playtagwidget.h"

PlayListTagGroupWidget::PlayListTagGroupWidget(database::TagGroup tGroup, QWidget *parent) :
    TagListGroupWidget(tGroup, parent)
{
    setTitle(tagGroup.getName());
//    tagsLabel->setText(AppGlobal::i()->getTextValue("tag/PlayListTag"));
//    QLabel* playListNameLabel = new QLabel(AppGlobal::i()->getTextValue("playlist/PlayListName"), this);

//    playListNameEdit = new QPushButton(AppGlobal::i()->getTextValue("common/None"), this);

//    mainLayout->insertWidget(0, playListNameEdit);
//    mainLayout->insertWidget(0, playListNameLabel);


    updateAvaliableTag();

}
//------------------------------------------------------------------------------
void PlayListTagGroupWidget::addTagWidget(database::Tag tag)
{
    PlayTagWidget* newWidget = new PlayTagWidget(tag, this);

    tagLayout->addWidget(newWidget);

    tagWidgetList.append(newWidget);
    if(!isChecked()) newWidget->hide();
}
