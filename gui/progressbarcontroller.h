#ifndef PROGRESSBARCONTROLLER_H
#define PROGRESSBARCONTROLLER_H

#include <QProgressBar>

class ProgressBarController : public QProgressBar
{
    Q_OBJECT
public:
    ProgressBarController(QWidget *parent = nullptr);

signals:
    void sigSetPosEvent(quint64 pos);

protected:
    void mousePressEvent(QMouseEvent *event);

};

#endif // PROGRESSBARCONTROLLER_H
