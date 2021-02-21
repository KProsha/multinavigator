#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMediaPlayer>

#include "progressbarcontroller.h"

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = nullptr);

    void setPlayer(QMediaPlayer* value);

signals:
    void sigPlay();
    void sigStop();
    void sigPause();
    void sigSetPosEvent(quint64 pos);

    void sigMute(bool);

protected slots:
    void setTimeLinePos(quint64 pos);
    void setDuration(quint64 duration);
    void onMediaPlayerStateChanged(QMediaPlayer::State newState);
    void onMediaPlayerMutedChanged(bool value);

    void onMuteButton();

protected:
    QMediaPlayer* player;

    QMediaPlayer::State state;

    bool muted;

    QPushButton* playPauseButton;
    QPushButton* backwardButton;
    QPushButton* stopButton;
    QPushButton* forwardButton;

    QPushButton* repeatButton;
    QPushButton* randomButton;

    ProgressBarController* timeLine;

    QPushButton* muteButton;
    ProgressBarController* volumeLevel;

protected slots:
    void onPlayPauseButton();


};

#endif // CONTROLWIDGET_H
