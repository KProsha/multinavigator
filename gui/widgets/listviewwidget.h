#ifndef LISTVIEWWIDGET_H
#define LISTVIEWWIDGET_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

#include "gui/widgets/idwidget.h"

class ListViewWidget : public QWidget
{    
public:
    explicit ListViewWidget(QWidget *parent = nullptr);

protected:
    QVBoxLayout* staticLayout;
    QVBoxLayout* dynamicLayout;

    QWidget* scrollWidget;

    QLabel* headerLabel;
    QList<QWidget*> widgetList;
};

#endif // LISTVIEWWIDGET_H
