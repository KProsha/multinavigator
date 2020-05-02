#include "playtagwidget.h"

#include <QLabel>
#include <QHBoxLayout>

#include <backend/appglobal.h>

PlayTagWidget::PlayTagWidget(database::Tag& t, QWidget *parent): TagWidget(t, parent)
{
    tagButton = new QPushButton(this);
    tagButton->setText(tag.getName());

    tagButton->setContentsMargins(5,0,0,0);

    tagButton->setStyleSheet ("text-align: left;"
                   "padding: 6px;"
                   );

    tagButton->setCheckable(true);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(tagButton);

    connect(tagButton, &QPushButton::clicked, this, &PlayTagWidget::onClick);
}
//------------------------------------------------------------------------------
bool PlayTagWidget::isChecked()
{
    return tagButton->isChecked();
}
//------------------------------------------------------------------------------
void PlayTagWidget::setChecked(bool b)
{
    tagButton->setChecked(b);
}
//------------------------------------------------------------------------------
void PlayTagWidget::onClick()
{
    emit sigClicked(tag.getId());
}

