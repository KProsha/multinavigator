#ifndef SCANOPTIONSWIDGET_H
#define SCANOPTIONSWIDGET_H

#include <QDialog>
#include <QCheckBox>
#include <QSpinBox>

class ScanOptionsWidget : public QDialog
{
    Q_OBJECT
public:
    explicit ScanOptionsWidget(QWidget *parent = nullptr);

signals:

protected slots:
    void onAccept();

protected:
    QCheckBox* useDirNameAsTag;
    QCheckBox* useFileNameAsTag;
    QCheckBox* useNumbersAsTag;
    QSpinBox*  fileNameCountForTag;

};

#endif // SCANOPTIONSWIDGET_H
