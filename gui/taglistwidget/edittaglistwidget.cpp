#include "edittaglistwidget.h"

#include "backend/appglobal.h"
#include "gui/tagwidget/edittagwidget.h"

EditTagListWidget::EditTagListWidget(QWidget *parent) : ListViewWidget(parent)
{
    headerLabel->setText(AppGlobal::i()->getTextValue("tag/Edit"));
    dynamicLayout->setSpacing(0);

    updateAvaliableTag();

    connect(AppGlobal::i()->getDataBase(), &database::DataBase::sigTagUpdated,
            this, &EditTagListWidget::updateAvaliableTag);
}
//------------------------------------------------------------------------------
void EditTagListWidget::updateAvaliableTag()
{
    foreach (auto w, widgetList) {
        w->deleteLater();
    }
    widgetList.clear();

    auto list = AppGlobal::i()->getDataBase()->getAllTags();

    std::sort(list.begin(), list.end(),
              [](const database::Tag& a, const database::Tag& b)->bool {
        if(a.getName() < b.getName()) return true;

        return false;
    });

    foreach (auto tag, list) {
        addTagWidget(tag);
    }
}

//------------------------------------------------------------------------------
void EditTagListWidget::addTagWidget(database::Tag tag)
{
    EditTagWidget* newWidget = new EditTagWidget(tag, scrollWidget);
    dynamicLayout->addWidget(newWidget);

    widgetList.append(newWidget);
}

