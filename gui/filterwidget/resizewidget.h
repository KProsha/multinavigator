#ifndef RESIZEWIDGET_H
#define RESIZEWIDGET_H

#include <QWidget>

class ResizeWidget : public QWidget
{
  Q_OBJECT
public:

  explicit ResizeWidget(QWidget *parent = nullptr);

signals:
  void sigExpandAll();
  void sigExpand();
  void sigHide();
  void sigHideAll();

public slots:
};

#endif // RESIZEWIDGET_H
