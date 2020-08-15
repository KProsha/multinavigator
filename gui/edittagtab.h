#ifndef EDITTAGTAB_H
#define EDITTAGTAB_H

#include <QWidget>

class EditTagTab : public QWidget
{
    Q_OBJECT
public:
    explicit EditTagTab(QWidget *parent = nullptr);

protected slots:
    void createNewTag();
protected:

};

#endif // EDITTAGTAB_H
