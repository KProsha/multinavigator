#include "edittaggrouptab.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>

#include "backend/appglobal.h"
#include "taggroup/edittaggrouplistwidget.h"

EditTagGroupTab::EditTagGroupTab(QWidget *parent) : QWidget(parent)
{
    QPushButton* newTagGroupButton = new QPushButton(AppGlobal::i()->getTextValue("tag/NewTagGroup"), this);
    EditTagGroupListWidget* tagListWidget = new EditTagGroupListWidget(this);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(newTagGroupButton);
    buttonLayout->addStretch();

    auto mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addItem(buttonLayout);
    mainLayout->addWidget(tagListWidget);

    connect(newTagGroupButton, &QPushButton::clicked, this, &EditTagGroupTab::createNewTagGroup);
}
//------------------------------------------------------------------------------
void EditTagGroupTab::createNewTagGroup()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                         AppGlobal::i()->getTextValue("tag/New"),
                                         AppGlobal::i()->getTextValue("tag/New"),
                                         QLineEdit::Normal,
                                         "",
                                         &ok);

    if(!ok) return;

    AppGlobal::i()->getDataBase()->addTagGroup(text);
}
