#include "edittaglistwidget.h"

#include "backend/appglobal.h"
#include "gui/tagwidget/edittagwidget.h"

EditTagListWidget::EditTagListWidget(QWidget *parent) : TagListWidget(parent)
{
    tagsLabel->setText(AppGlobal::i()->getTextValue("tag/Edit"));

    updateAvaliableTag();
}
//------------------------------------------------------------------------------
void EditTagListWidget::addTagWidget(database::Tag tag)
{
    EditTagWidget* newWidget = new EditTagWidget(tag, scrollTagListWidget);
//    connect(newWidget, &TagWidget::clicked, this, &TagListWidget::onTagClicked);

    tagLayout->addWidget(newWidget);

    tagWidgetList.append(newWidget);
}
//------------------------------------------------------------------------------
