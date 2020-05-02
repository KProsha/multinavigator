#include "progressbarcontroller.h"

#include <QMouseEvent>
#include <QDebug>

ProgressBarController::ProgressBarController(QWidget *parent):QProgressBar (parent)
{

}
//------------------------------------------------------------------------------
void ProgressBarController::mousePressEvent(QMouseEvent *event)
{
    float part = ((float)event->x()/ (float)width());
    quint64 newPos = part * maximum();

    emit sigSetPosEvent(newPos);
}

