#include "filetaggroupwidget.h"

#include "backend/appglobal.h"
#include "gui/tagwidget/filetagwidget.h"

FileTagGroupWidget::FileTagGroupWidget(database::TagGroup tGroup, QWidget *parent) :
    TagListGroupWidget(tGroup, parent)
{  
    setTitle(tagGroup.getName());
    connect(AppGlobal::i(), &AppGlobal::sigNewCurrentFile, this, &FileTagGroupWidget::updateFileTag);
    connect(AppGlobal::i()->getDataBase(), &database::DataBase::sigFileTagUpdated, this, &FileTagGroupWidget::updateFileTag);
    updateAvaliableTag();
}
//------------------------------------------------------------------------------
void FileTagGroupWidget::updateFileTag()
{
    int id = AppGlobal::i()->getCurrentFileId();
    if(id == -1) return;

    auto fileTagList = AppGlobal::i()->getDataBase()->getFileTag(id);

    foreach (auto widget, tagWidgetList) {
        auto playTagWidget = dynamic_cast<FileTagWidget*>(widget);
        if(!playTagWidget) continue;

        playTagWidget->setEnabled(true);
        playTagWidget->setChecked(false);
        foreach (auto fileTag, fileTagList) {
            if(playTagWidget->getId() == fileTag.getId()){
                playTagWidget->setChecked(true);
            }
        }
    }
}
//------------------------------------------------------------------------------
void FileTagGroupWidget::onTagClicked(int tagId)
{
    int id = AppGlobal::i()->getCurrentFileId();
    if(id == -1) return;

    AppGlobal::i()->getDataBase()->toggleFileTag(id, tagId);
}
//------------------------------------------------------------------------------
void FileTagGroupWidget::addTagWidget(database::Tag tag)
{
    FileTagWidget* newWidget = new FileTagWidget(tag, this);
    connect(newWidget, &FileTagWidget::sigClicked, this, &FileTagGroupWidget::onTagClicked);

    tagLayout->addWidget(newWidget);

    tagWidgetList.append(newWidget);
    if(!isChecked()) newWidget->hide();
}
