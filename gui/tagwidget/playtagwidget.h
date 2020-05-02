#ifndef PLAYTAGWIDGET_H
#define PLAYTAGWIDGET_H

#include "tagwidget.h"

class PlayTagWidget : public TagWidget
{    
Q_OBJECT
public:
    explicit PlayTagWidget(database::Tag& t, QWidget *parent = nullptr);

    bool isChecked();
    void setChecked(bool b);
signals:
    void sigClicked(int tagId);

protected:
    QPushButton* tagButton;

protected slots:
    void onClick();

};

#endif // PLAYTAGWIDGET_H
