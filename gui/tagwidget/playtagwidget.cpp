#include "playtagwidget.h"

#include <QLabel>
#include <QHBoxLayout>

#include <backend/appglobal.h>

PlayTagWidget::PlayTagWidget(database::Tag& t, QWidget *parent): IdWidget<QFrame>(t.getId(), parent)
{
    QString tagText = t.getName();
    int textLength = AppGlobal::i()->getUserOptions()->getMaxDisplayedTagLength();
    if(tagText.size() >= textLength){
        tagText.truncate(textLength - 3);
        tagText.append("...");
    }

    auto nameLabel = new QLabel(tagText, this);

    orButton = new QPushButton("+" ,this);
    orButton->setCheckable(true);
    orButton->setFixedWidth(20);

    andButton = new QPushButton("&&" ,this);
    andButton->setCheckable(true);
    andButton->setFixedWidth(20);

    notButton = new QPushButton("-" ,this);
    notButton->setCheckable(true);
    notButton->setFixedWidth(20);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(orButton);
    mainLayout->addWidget(andButton);
    mainLayout->addWidget(notButton);
    mainLayout->addWidget(nameLabel);

    connect(orButton, &QPushButton::clicked, this, &PlayTagWidget::onClick);
    connect(andButton, &QPushButton::clicked, this, &PlayTagWidget::onClick);
    connect(notButton, &QPushButton::clicked, this, &PlayTagWidget::onClick);

    connect(this, &PlayTagWidget::sigTagFilterChanged, AppGlobal::i(), &AppGlobal::setTagIdFilter);
}
//------------------------------------------------------------------------------
void PlayTagWidget::onClick(bool checked)
{
    database::Tag::ESelectionType type = database::Tag::NotSelected;

    if((sender() == orButton) && checked){
        andButton->setChecked(false);
        notButton->setChecked(false);
        type = database::Tag::TypeOr;
    }
    if((sender() == andButton) && checked){
        notButton->setChecked(false);
        orButton->setChecked(false);
        type = database::Tag::TypeAnd;
    }
    if((sender() == notButton) && checked){
        andButton->setChecked(false);
        orButton->setChecked(false);
        type = database::Tag::TypeNot;
    }

    emit sigTagFilterChanged(getId(), type);
}

