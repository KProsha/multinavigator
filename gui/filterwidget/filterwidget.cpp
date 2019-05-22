#include "filterwidget.h"

#include <QHBoxLayout>
#include <QLabel>

#include "database/database.h"
#include "options/textvalue.h"
#include "resizewidget.h"

FilterWidget::FilterWidget(QWidget *parent) : QWidget(parent)
{
  ResizeWidget* ResizeWidgetI = new ResizeWidget(this);

  dirLabel = new QLabel(TextValue::I->noDirectory());
  QLabel* HeadLabel = new QLabel(TextValue::I->filters());

  centralLayout = new QVBoxLayout();
  centralLayout->addWidget(dirLabel);
  centralLayout->addWidget(HeadLabel);

  QHBoxLayout* MainLayout = new QHBoxLayout(this);
  MainLayout->setContentsMargins(0,5,0,5);
  MainLayout->setSpacing(10);
  MainLayout->addWidget(ResizeWidgetI);
  MainLayout->addLayout(centralLayout);

}
//------------------------------------------------------------------------------
void FilterWidget::clearTagWidgetList()
{ 
  foreach (auto TagWidget, tagWidgetList) {
    TagWidget->deleteLater();
  }
  tagWidgetList.clear();
}
//------------------------------------------------------------------------------
void FilterWidget::updateDirTag()
{  
  clearTagWidgetList();

  foreach(auto tag, database::DataBase::i->tagTable->getTagList() ){
    if(tag->name == "root") continue;

    TagWidget* TagWidgetI = new TagWidget(this);
    TagWidgetI->setToolTip(tag->name);

    QString ShortName = tag->name;

    int MaxLength = 25;
    if(tag->name.length() > MaxLength){
      ShortName.truncate(MaxLength - 3);
      ShortName.append("...");
    }

    TagWidgetI->setText(ShortName);

    centralLayout->addWidget(TagWidgetI);

    tagWidgetList.append(TagWidgetI);
  }
  centralLayout->addStretch(1);
}
