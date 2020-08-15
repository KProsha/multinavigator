#ifndef EDITTAGGROUPTAB_H
#define EDITTAGGROUPTAB_H

#include <QWidget>

class EditTagGroupTab : public QWidget
{
    Q_OBJECT
public:
    explicit EditTagGroupTab(QWidget *parent = nullptr);

protected slots:
    void createNewTagGroup();
protected:

};

#endif // EDITTAGGROUPTAB_H
