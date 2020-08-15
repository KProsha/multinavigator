#include "taglistgroupwidget.h"

#include <QHBoxLayout>

#include "backend/appglobal.h"
#include "gui/tagwidget/playtagwidget.h"


TagListGroupWidget::TagListGroupWidget(database::TagGroup tGroup, QWidget *parent) : QGroupBox(parent)
{  
    setCheckable(true);
    tagGroup = tGroup;
    tagLayout = new QVBoxLayout();
    setLayout(tagLayout);

    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
//    tagLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    connect(this, &TagListGroupWidget::clicked,
            this, &TagListGroupWidget::minimizeMaximize);

    connect(AppGlobal::i()->getDataBase(), &database::DataBase::sigTagGroupTagUpdated,
            this, &TagListGroupWidget::updateAvaliableTag);
    connect(AppGlobal::i()->getDataBase(), &database::DataBase::sigTagUpdated,
            this, &TagListGroupWidget::updateAvaliableTag);
}
//------------------------------------------------------------------------------
void TagListGroupWidget::updateAvaliableTag()
{
    foreach (auto w, tagWidgetList) {
        w->deleteLater();
    }
    tagWidgetList.clear();

    auto list = AppGlobal::i()->getDataBase()->getTagList(tagGroup.getId());

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
void TagListGroupWidget::minimizeMaximize()
{
    if(isChecked()){
        foreach (auto w, tagWidgetList) w->show();
    }else{
        foreach (auto w, tagWidgetList) w->hide();
    }
}

