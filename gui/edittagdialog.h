#ifndef EDITTAGDIALOG_H
#define EDITTAGDIALOG_H

#include <QDialog>

class EditTagListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditTagListDialog(QWidget *parent = nullptr);

signals:

protected slots:
    void createNewTag();

protected:

};

#endif // EDITTAGDIALOG_H
