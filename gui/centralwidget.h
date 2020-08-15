#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QVideoWidget>

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSplitter>
#include <QTimer>

#include "videowidget.h"
#include "playlistwidget.h"
#include "backend/appglobal.h"
#include "controlwidget.h"
#include "taglistwidget/taglistwidget.h"
#include "taglistwidget/playlisttaggroupwidget.h"

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = nullptr);

signals:
    void sigNameOfPlaingMedia(QString );

public slots:
    void setState(AppGlobal::EAppState newState);

protected:
    VideoWidget* videoWidget;
    PlaylistWidget* playlistWidget;
    TagListWidget<FileTagGroupWidget>* fileTagListWidget;
    TagListWidget<PlayListTagGroupWidget>* playListTagWidget;
    ControlWidget* controlWidget;

    QMediaPlayer* player;
    QMediaPlaylist* playList;

    QTimer* hideControlTimer;

public slots:
    void playFile();
};

#endif // CENTRALWIDGET_H
