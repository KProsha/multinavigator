#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QVideoWidget>

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSplitter>

#include "filterwidget/filterwidget.h"
#include "videowidget.h"

class CentralWidget : public QWidget
{
  Q_OBJECT

  QMediaPlayer* player;
  QMediaPlaylist* playList;



  QSplitter* splitter;

  void playFile(const QString& name);
public:
  explicit CentralWidget(QWidget *parent = nullptr);  

  VideoWidget* videoWidget;
  FilterWidget* filterWidget;

  void setFullScreenMode(bool b){
    if(b){
      filterWidget->setVisible(false);
    }else {
      filterWidget->setVisible(true);
    }

  }


signals:
  void sigSwitchFullScreen();
  void sigNameOfPlaingMedia(QString );


public slots:



};

#endif // CENTRALWIDGET_H
