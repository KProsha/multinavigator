#include "edittagwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>

#include "backend/appglobal.h"

EditTagWidget::EditTagWidget(database::Tag& t, QWidget *parent) : TagWidget(t, parent)
{
    auto mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    QLabel* nameLabel = new QLabel(tag.getName());
    QPushButton* removeButton = new QPushButton(AppGlobal::i()->getTextValue("tag/Remove"));
    QPushButton* renameButton = new QPushButton(AppGlobal::i()->getTextValue("tag/Rename"));

    nameLabel->setFixedWidth(400);

    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(removeButton);
    mainLayout->addWidget(renameButton);

    connect(removeButton, &QPushButton::clicked, this, &EditTagWidget::onRemove);
    connect(renameButton, &QPushButton::clicked, this, &EditTagWidget::onRename);
}
//------------------------------------------------------------------------------
void EditTagWidget::onRename()
{
    bool ok;
    QString text = QInputDialog::getText(this, AppGlobal::i()->getTextValue("tag/Rename"),
                                         QString("%1 '%2'").arg(AppGlobal::i()->getTextValue("tag/Rename"), tag.getName()),
                                         QLineEdit::Normal,
                                         tag.getName(),
                                         &ok);
    if (!ok || text.isEmpty()) return;

    if(!AppGlobal::i()->getDataBase()->renameTag(tag.getId(), text)){
        QMessageBox message;
        message.setText(QString("%1 '%2'").arg(AppGlobal::i()->getTextValue("tag/WrongName"), tag.getName()));
        message.exec();
    }
}
//------------------------------------------------------------------------------
void EditTagWidget::onRemove()
{
    AppGlobal::i()->getDataBase()->removeTag(tag.getId());
}






