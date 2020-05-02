#include "filetaglistwidget.h"

#include "backend/appglobal.h"
#include "gui/tagwidget/playtagwidget.h"

FileTagListWidget::FileTagListWidget(QWidget *parent) : TagListWidget(parent)
{  
    tagsLabel->setText(AppGlobal::i()->getTextValue("tag/FileTagList"));
    connect(AppGlobal::i(), &AppGlobal::sigNewCurrentFile, this, &FileTagListWidget::updateFileTag);
    connect(AppGlobal::i()->getDataBase(), &database::DataBase::sigFileTagUpdated, this, &FileTagListWidget::updateFileTag);
}
//------------------------------------------------------------------------------
void FileTagListWidget::updateFileTag()
{
    int id = AppGlobal::i()->getCurrentFileId();
    if(id == -1) return;

    auto fileTagList = AppGlobal::i()->getDataBase()->getFileTag(id);

    foreach (auto widget, tagWidgetList) {
        auto playTagWidget = dynamic_cast<PlayTagWidget*>(widget);
        if(!playTagWidget) continue;

        playTagWidget->setEnabled(true);
        playTagWidget->setChecked(false);
        foreach (auto fileTag, fileTagList) {
            if(playTagWidget->getTagId() == fileTag.getId()){
                playTagWidget->setChecked(true);
            }
        }
    }
}
//------------------------------------------------------------------------------
void FileTagListWidget::onTagClickedImpl(int tagId)
{
    int id = AppGlobal::i()->getCurrentFileId();
    if(id == -1) return;

    AppGlobal::i()->getDataBase()->toggleFileTag(id, tagId);
}
//------------------------------------------------------------------------------
