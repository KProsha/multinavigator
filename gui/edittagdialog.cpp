#include "edittagdialog.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QInputDialog>

#include "backend/appglobal.h"
#include "taglistwidget/edittaglistwidget.h"
#include "edittagtab.h"
#include "edittaggrouptab.h"

EditTagDialog::EditTagDialog(QWidget *parent) : QDialog(parent)
{
    auto tag = new QTabWidget(this);

    auto tagWidget = new EditTagTab(tag);
    auto tagGroupWidget = new EditTagGroupTab(tag);

    tag->addTab(tagWidget, AppGlobal::i()->getTextValue("tag/Tags"));
    tag->addTab(tagGroupWidget, AppGlobal::i()->getTextValue("tag/Group"));

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    auto mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addWidget(tag);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);    
}

