#include "filetagwidget.h"

#include <QLabel>
#include <QHBoxLayout>

#include <backend/appglobal.h>

FileTagWidget::FileTagWidget(database::Tag& t, QWidget *parent): IdWidget<QFrame>(t.getId(), parent)
{
    tagButton = new QPushButton(this);
    QString tagText = t.getName();

    int textLength = AppGlobal::i()->getUserOptions()->getMaxDisplayedTagLength();
    if(tagText.size() >= textLength){
        tagText.truncate(textLength - 3);
        tagText.append("...");
    }

    tagButton->setText(tagText);


    tagButton->setContentsMargins(5,0,0,0);

    tagButton->setStyleSheet ("text-align: left;"
                              "padding: 6px;"
                              );

    tagButton->setCheckable(true);


    QHBoxLayout* mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(tagButton);


    connect(tagButton, &QPushButton::clicked, this, &FileTagWidget::onClick);
}
//------------------------------------------------------------------------------
bool FileTagWidget::isChecked()
{
    return tagButton->isChecked();
}
//------------------------------------------------------------------------------
void FileTagWidget::setChecked(bool b)
{
    tagButton->setChecked(b);
}
//------------------------------------------------------------------------------
void FileTagWidget::onClick()
{
    emit sigClicked(getId());
}
