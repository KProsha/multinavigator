#include "videowidget.h"

#include "backend/appglobal.h"

#include <QDebug>

void VideoWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
    Q_UNUSED(e)
    emit sigMouseDoubleClick();
}
//------------------------------------------------------------------------------
void VideoWidget::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    if(AppGlobal::i()->getState() != AppGlobal::StateFullScreen) return;

    emit sigMousePressedInFullScreen();
}
