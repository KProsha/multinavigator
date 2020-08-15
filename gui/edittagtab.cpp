#include "edittagtab.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>

#include "backend/appglobal.h"
#include "taglistwidget/edittaglistwidget.h"

EditTagTab::EditTagTab(QWidget *parent) : QWidget(parent)
{
    QPushButton* newTagButton = new QPushButton(AppGlobal::i()->getTextValue("tag/New"), this);
    EditTagListWidget* tagListWidget = new EditTagListWidget(this);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(newTagButton);
    buttonLayout->addStretch();

    auto mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addItem(buttonLayout);
    mainLayout->addWidget(tagListWidget);

    connect(newTagButton, &QPushButton::clicked, this, &EditTagTab::createNewTag);
}
//------------------------------------------------------------------------------
void EditTagTab::createNewTag()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                         AppGlobal::i()->getTextValue("tag/New"),
                                         AppGlobal::i()->getTextValue("tag/New"),
                                         QLineEdit::Normal,
                                         "",
                                         &ok);

    if(!ok) return;

    AppGlobal::i()->getDataBase()->addTag(text);
}

