#include "taglistwidget.h"

#include <QHBoxLayout>

#include "backend/appglobal.h"
#include "gui/tagwidget/playtagwidget.h"


TagListWidget::TagListWidget(QWidget *parent) : QWidget(parent)
{
    tagsLabel = new QLabel(this);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollTagListWidget = new QWidget(scrollArea);

    scrollArea->setWidget(scrollTagListWidget);
    tagLayout = new QVBoxLayout();
    tagLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    scrollTagListWidget->setLayout(tagLayout);

    QVBoxLayout* staticLayout = new QVBoxLayout();
    setLayout(staticLayout);

    staticLayout->addWidget(tagsLabel);
    staticLayout->addWidget(scrollArea);

    connect(AppGlobal::i()->getDataBase(), &database::DataBase::sigTagUpdated,
            this, &TagListWidget::updateAvaliableTag);
}
//------------------------------------------------------------------------------
void TagListWidget::updateAvaliableTag()
{
    foreach (auto w, tagWidgetList) {
        w->deleteLater();
    }
    tagWidgetList.clear();

    auto list = AppGlobal::i()->getDataBase()->getAllTags();
    list.size();

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
void TagListWidget::onTagClicked(int tagId)
{
    onTagClickedImpl(tagId);
}
//------------------------------------------------------------------------------
void TagListWidget::addTagWidget(database::Tag tag)
{
    PlayTagWidget* newWidget = new PlayTagWidget(tag, scrollTagListWidget);
    connect(newWidget, &PlayTagWidget::sigClicked, this, &TagListWidget::onTagClicked);

    tagLayout->addWidget(newWidget);

    tagWidgetList.append(newWidget);
}
