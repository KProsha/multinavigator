#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QButtonGroup>

#include "options/textvalue.h"
#include "tagwidget.h"


class FilterWidget : public QWidget
{
  Q_OBJECT
  QLabel* dirLabel;
  QVBoxLayout* centralLayout;

  QList<TagWidget*> tagWidgetList;

public:
  explicit FilterWidget(QWidget *parent = nullptr);

  void clearTagWidgetList();

signals:

public slots:
  void setDirName(const QString& name){dirLabel->setText(TextValue::I->directory() + ": " + name);}

  void updateDirTag();

};

#endif // FILTERWIDGET_H
