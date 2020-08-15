#include "edittaggroupwidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QCheckBox>

#include "backend/appglobal.h"

EditTagGroupWidget::EditTagGroupWidget(database::TagGroup& t, QWidget *parent) : IdWidget<QFrame>(t.getId(), parent)
{
    setFrameStyle(QFrame::Panel);

    mainLayout = new QHBoxLayout();
    mainLayout->setMargin(5);
    setLayout(mainLayout);

    nameLabel = new QLabel(t.getName());
    QPushButton* removeButton = new QPushButton(AppGlobal::i()->getTextValue("tag/Remove"));
    QPushButton* renameButton = new QPushButton(AppGlobal::i()->getTextValue("tag/Rename"));

    nameLabel->setFixedWidth(400);

    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(removeButton);
    mainLayout->addWidget(renameButton);
    //----- -----

    connect(removeButton, &QPushButton::clicked, this, &EditTagGroupWidget::onRemove);
    connect(renameButton, &QPushButton::clicked, this, &EditTagGroupWidget::onRename);
}
//------------------------------------------------------------------------------
void EditTagGroupWidget::onRename()
{
    bool ok;
    QString text = QInputDialog::getText(this, AppGlobal::i()->getTextValue("tag/Rename"),
                                         QString("%1 '%2'").arg(AppGlobal::i()->getTextValue("tag/Rename"),
                                                                nameLabel->text()),
                                         QLineEdit::Normal,
                                         nameLabel->text(),
                                         &ok);
    if (!ok || text.isEmpty()) return;

    if(!AppGlobal::i()->getDataBase()->renameTagGroup(getId(), text)){
        QMessageBox message;
        message.setText(QString("%1 '%2'").arg(AppGlobal::i()->getTextValue("tag/WrongName"), nameLabel->text()));
        message.exec();
    }
}
//------------------------------------------------------------------------------
void EditTagGroupWidget::onRemove()
{
    AppGlobal::i()->getDataBase()->removeTagGroup(getId());
}
//------------------------------------------------------------------------------
void EditTagGroupWidget::onTagGroupCheckBox(bool checked)
{
    auto tagGroupCheckBox = dynamic_cast<IdWidget<QCheckBox>* >(sender());
    if(!tagGroupCheckBox) return;
    AppGlobal::i()->getDataBase()->toggleTagGroupTag(tagGroupCheckBox->getId() ,getId(), checked);

}







