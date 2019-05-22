#include "centralwidget.h"

#include <QMouseEvent>
#include <QSplitter>

#include <QHBoxLayout>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
  QHBoxLayout* Layout = new QHBoxLayout(this);
  Layout->setContentsMargins(0,0,0,0);

  videoWidget = new VideoWidget(this);
  filterWidget = new FilterWidget(this);

  QMediaPlayer* Player = new QMediaPlayer(this,QMediaPlayer::VideoSurface);

  Player->setVideoOutput(videoWidget);

  Layout->addWidget(videoWidget);
  Layout->addWidget(filterWidget);

  setLayout(Layout);

 // setContentsMargins(0,0,0,0);

  connect(videoWidget, &VideoWidget::sigMouseDoubleClick, this, &CentralWidget::sigSwitchFullScreen);
}
//------------------------------------------------------------------------------
void CentralWidget::playFile(const QString& name)
{
  player->setMedia(QUrl("file://" + name));
  player->play();
  emit(sigNameOfPlaingMedia(name));

}





