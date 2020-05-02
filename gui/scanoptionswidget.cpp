#include "scanoptionswidget.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>

#include "backend/appglobal.h"

ScanOptionsWidget::ScanOptionsWidget(QWidget *parent) : QDialog(parent)
{
    useDirNameAsTag = new QCheckBox(AppGlobal::i()->getTextValue("scanoptions/useDirNameAsTag"), this);
    useDirNameAsTag->setChecked(AppGlobal::i()->getUserOptions()->getUseDirNameAsTag());

    useFileNameAsTag = new QCheckBox(AppGlobal::i()->getTextValue("scanoptions/useFileNameAsTag"), this);
    useFileNameAsTag->setChecked(AppGlobal::i()->getUserOptions()->getUseFileNameAsTag());

    useNumbersAsTag = new QCheckBox(AppGlobal::i()->getTextValue("scanoptions/useNumbersAsTag"), this);
    useNumbersAsTag->setChecked(AppGlobal::i()->getUserOptions()->getUseNumbersAsTag());

    fileNameCountForTag = new QSpinBox(this);
    fileNameCountForTag->setValue(AppGlobal::i()->getUserOptions()->getFileNameCountForTag());
    fileNameCountForTag->setMinimum(3);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ScanOptionsWidget::onAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto fileNameAsTagLayout = new QHBoxLayout();
    fileNameAsTagLayout->addWidget(useFileNameAsTag);
    fileNameAsTagLayout->addWidget(fileNameCountForTag);
    fileNameAsTagLayout->addStretch();

    auto mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addWidget(useDirNameAsTag);
    mainLayout->addWidget(useNumbersAsTag);
    mainLayout->addLayout(fileNameAsTagLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonBox);

    setWindowTitle(AppGlobal::i()->getTextValue("scanoptions/title"));
}
//------------------------------------------------------------------------------
void ScanOptionsWidget::onAccept()
{
    AppGlobal::i()->getUserOptions()->setUseDirNameAsTag(useDirNameAsTag->isChecked());
    AppGlobal::i()->getUserOptions()->setUseNumbersAsTag(useNumbersAsTag->isChecked());
    AppGlobal::i()->getUserOptions()->setUseFileNameAsTag(useFileNameAsTag->isChecked());
    AppGlobal::i()->getUserOptions()->setFileNameCountForTag(fileNameCountForTag->value());

    accept();
}
//------------------------------------------------------------------------------

