#include "edittaggrouplistwidget.h"

#include "backend/appglobal.h"
#include "gui/taggroup/edittaggroupwidget.h"

EditTagGroupListWidget::EditTagGroupListWidget(QWidget *parent) : ListViewWidget(parent)
{
    headerLabel->setText(AppGlobal::i()->getTextValue("tag/Edit"));
    dynamicLayout->setSpacing(0);

    updateAvaliableTagGroup();

    connect(AppGlobal::i()->getDataBase(), &database::DataBase::sigTagGroupUpdated,
            this, &EditTagGroupListWidget::updateAvaliableTagGroup);
}
//------------------------------------------------------------------------------
void EditTagGroupListWidget::updateAvaliableTagGroup()
{
    foreach (auto w, widgetList) {
        w->deleteLater();
    }
    widgetList.clear();

    auto list = AppGlobal::i()->getDataBase()->getAllTagGroups();

    std::sort(list.begin(), list.end(),
              [](const database::TagGroup& a, const database::TagGroup& b)->bool {
        if(a.getName() < b.getName()) return true;

        return false;
    });

    foreach (auto tag, list) {
        EditTagGroupWidget* newWidget = new EditTagGroupWidget(tag, scrollWidget);
        dynamicLayout->addWidget(newWidget);

        widgetList.append(newWidget);
    }
}

//------------------------------------------------------------------------------


