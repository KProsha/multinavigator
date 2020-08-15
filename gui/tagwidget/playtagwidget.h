#ifndef PLAYTAGWIDGET_H
#define PLAYTAGWIDGET_H

#include "gui/widgets/idwidget.h"

#include <QFrame>
#include <QHBoxLayout>

class PlayTagWidget : public IdWidget<QFrame>
{    
Q_OBJECT
public:
    explicit PlayTagWidget(database::Tag& t, QWidget *parent = nullptr);
signals:
    void sigTagFilterChanged(int id, database::Tag::ESelectionType type);

protected slots:
    void onClick(bool checked);

protected:
    QPushButton* orButton;
    QPushButton* andButton;
    QPushButton* notButton;

};

#endif // PLAYTAGWIDGET_H
