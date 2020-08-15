#ifndef FILETAGWIDGET_H
#define FILETAGWIDGET_H

#include "gui/widgets/idwidget.h"

#include <QFrame>
#include <QHBoxLayout>

class FileTagWidget : public IdWidget<QFrame>
{    
    Q_OBJECT
public:
    explicit FileTagWidget(database::Tag& t, QWidget *parent = nullptr);
    bool isChecked();
    void setChecked(bool b);
signals:
    void sigClicked(int tagId);

protected:
    QPushButton* tagButton;

protected slots:
    void onClick();
};

#endif // FILETAGWIDGET_H
