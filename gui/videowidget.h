#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>

class VideoWidget : public QVideoWidget
{
  Q_OBJECT
public:
  explicit VideoWidget(QWidget *parent = nullptr):QVideoWidget(parent){}

  void mouseDoubleClickEvent(QMouseEvent* e){
    (void)e;
    emit sigMouseDoubleClick();
  }

signals:
  void sigMouseDoubleClick();

public slots:
};

#endif // VIDEOWIDGET_H
