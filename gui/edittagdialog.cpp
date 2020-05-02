#include "edittagdialog.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>

#include "backend/appglobal.h"
#include "taglistwidget/edittaglistwidget.h"

EditTagListDialog::EditTagListDialog(QWidget *parent) : QDialog(parent)
{
    QPushButton* newTagButton = new QPushButton(AppGlobal::i()->getTextValue("tag/New"), this);
    EditTagListWidget* tagListWidget = new EditTagListWidget(this);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    auto newTagButtonLayout = new QHBoxLayout();
    newTagButtonLayout->addWidget(newTagButton);
    newTagButtonLayout->addStretch();

    auto mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addItem(newTagButtonLayout);
    mainLayout->addWidget(tagListWidget);
    mainLayout->addWidget(buttonBox);

    connect(newTagButton, &QPushButton::clicked, this, &EditTagListDialog::createNewTag);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
}

//------------------------------------------------------------------------------
void EditTagListDialog::createNewTag()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                         AppGlobal::i()->getTextValue("tag/New"),
                                         AppGlobal::i()->getTextValue("tag/New"),
                                         QLineEdit::Normal,
                                         "",
                                         &ok);

    if(!ok) return;

    AppGlobal::i()->getDataBase()->addTag(text, database::Tag::TypeUser);
}
