#include "listviewwidget.h"


ListViewWidget::ListViewWidget(QWidget *parent) : QWidget(parent)
{
    headerLabel = new QLabel(this);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollWidget = new QWidget(scrollArea);

    scrollArea->setWidget(scrollWidget);
    dynamicLayout = new QVBoxLayout();
    dynamicLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    scrollWidget->setLayout(dynamicLayout);

    staticLayout = new QVBoxLayout();
    setLayout(staticLayout);

    staticLayout->addWidget(headerLabel);
    staticLayout->addWidget(scrollArea);
}


