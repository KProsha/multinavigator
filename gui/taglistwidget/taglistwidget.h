#ifndef FILETAGLISTWIDGET_H
#define FILETAGLISTWIDGET_H

#include "gui/widgets/listviewwidget.h"

#include "filetaggroupwidget.h"
#include "backend/appglobal.h"

class GroupListWidget: public ListViewWidget
{
    Q_OBJECT
public:
    explicit GroupListWidget(QWidget *parent = nullptr): ListViewWidget(parent){
        connect(AppGlobal::i()->getDataBase(), &database::DataBase::sigTagGroupUpdated,
                this, &GroupListWidget::updateGroups);
    }
protected slots:
    virtual void updateGroups() = 0;
};

template<class T>
class TagListWidget: public GroupListWidget
{    
public:
    explicit TagListWidget(QWidget *parent = nullptr): GroupListWidget(parent){}

protected:
    void updateGroups() override{
        foreach (auto widget, widgetList) {
            widget->deleteLater();
        }
        widgetList.clear();

        auto tagGroupList =  AppGlobal::i()->getDataBase()->getAllTagGroups();

        foreach (database::TagGroup tagGroup, tagGroupList) {
            addNewTagGroup(tagGroup);
        }
    }

    void addNewTagGroup(database::TagGroup tagGroup){
        auto groupWidget = new T(tagGroup, this);
        dynamicLayout->addWidget(groupWidget);
        widgetList.append(groupWidget);
    }

};

#endif // FILETAGLISTWIDGET_H
