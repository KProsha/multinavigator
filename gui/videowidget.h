#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>


class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr):QVideoWidget(parent){}

    void mouseDoubleClickEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent *e);


signals:
    void sigMouseDoubleClick();
    void sigMousePressedInFullScreen();

public slots:
};



#endif // VIDEOWIDGET_H
