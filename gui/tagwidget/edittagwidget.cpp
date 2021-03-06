#include "edittagwidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QCheckBox>

#include "backend/appglobal.h"

EditTagWidget::EditTagWidget(database::Tag& t, QWidget *parent) : IdWidget<QFrame>(t.getId(), parent)
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
    updateTagGroups();
    //----- -----

    connect(removeButton, &QPushButton::clicked, this, &EditTagWidget::onRemove);
    connect(renameButton, &QPushButton::clicked, this, &EditTagWidget::onRename);

    connect(AppGlobal::i()->getDataBase(), &database::DataBase::sigTagGroupUpdated,
            this, &EditTagWidget::updateTagGroups);
}
//------------------------------------------------------------------------------
void EditTagWidget::onRename()
{
    bool ok;
    QString text = QInputDialog::getText(this, AppGlobal::i()->getTextValue("tag/Rename"),
                                         QString("%1 '%2'").arg(AppGlobal::i()->getTextValue("tag/Rename"),
                                                                nameLabel->text()),
                                         QLineEdit::Normal,
                                         nameLabel->text(),
                                         &ok);
    if (!ok || text.isEmpty()) return;

    if(!AppGlobal::i()->getDataBase()->renameTag(getId(), text)){
        QMessageBox message;
        message.setText(QString("%1 '%2'").arg(AppGlobal::i()->getTextValue("tag/WrongName"), nameLabel->text()));
        message.exec();
    }
}
//------------------------------------------------------------------------------
void EditTagWidget::onRemove()
{
    AppGlobal::i()->getDataBase()->removeTag(getId());
}
//------------------------------------------------------------------------------
void EditTagWidget::onTagGroupCheckBox(bool checked)
{
    auto tagGroupCheckBox = dynamic_cast<IdWidget<QCheckBox>* >(sender());
    if(!tagGroupCheckBox) return;
    AppGlobal::i()->getDataBase()->toggleTagGroupTag(tagGroupCheckBox->getId() ,getId(), checked);

}
//------------------------------------------------------------------------------
void EditTagWidget::updateTagGroups()
{
    foreach (auto w, tagGroupWidgets) {
        w->deleteLater();
    }
    tagGroupWidgets.clear();

    QList<quint64> enabledTagGroupsId = AppGlobal::i()->getDataBase()->getTagGroupsId(getId());

    foreach (auto i, AppGlobal::i()->getDataBase()->getAllTagGroups()) {
        auto tagGroupCheckBox = new IdWidget<QCheckBox>(i.getId(), this);
        tagGroupCheckBox->setText(i.getName());
        connect(tagGroupCheckBox, &QCheckBox::clicked, this, &EditTagWidget::onTagGroupCheckBox);
        tagGroupCheckBox->setFixedWidth(150);
        mainLayout->addWidget(tagGroupCheckBox);
        tagGroupWidgets.append(tagGroupCheckBox);
        foreach (quint64 groupId, enabledTagGroupsId) {
            if(i.getId() == groupId){
                tagGroupCheckBox->setChecked(true);
                break;
            }
        }
    }
}






