#include "playlisttagwidget.h"

#include "backend/appglobal.h"
#include "gui/tagwidget/playtagwidget.h"

PlayListTagWidget::PlayListTagWidget(QWidget *parent) : TagListWidget(parent)
{    
    tagsLabel->setText(AppGlobal::i()->getTextValue("tag/PlayListTag"));
//    QLabel* playListNameLabel = new QLabel(AppGlobal::i()->getTextValue("playlist/PlayListName"), this);

//    playListNameEdit = new QPushButton(AppGlobal::i()->getTextValue("common/None"), this);

//    mainLayout->insertWidget(0, playListNameEdit);
//    mainLayout->insertWidget(0, playListNameLabel);

}
//------------------------------------------------------------------------------
void PlayListTagWidget::onTagClickedImpl(int tagId)
{
    Q_UNUSED(tagId)

    QList<int> selected;
    foreach (auto widget, tagWidgetList) {
        auto playTagWidget = dynamic_cast<PlayTagWidget*>(widget);
        if(!playTagWidget) continue;

        if(playTagWidget->isChecked()){
            selected.append(widget->getTagId());
        }
    }

    emit sigTagSelected(selected);
}
