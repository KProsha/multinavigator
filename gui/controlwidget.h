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

    enum EState
    {
        StateStopped,
        StatePlaying,
        StatePaused
    };

    void setState(EState newState);

signals:
    void sigPlay();
    void sigStop();
    void sigPause();
    void sigSetPosEvent(quint64 pos);

public slots:
    void setTimeLinePos(quint64 pos);
    void setDuration(quint64 duration);
    void onMediaPlayerStateChanged(QMediaPlayer::State state);


protected:
    EState state;

    QPushButton* playPauseButton;
    QPushButton* backwardButton;
    QPushButton* stopButton;
    QPushButton* forwardButton;

    QPushButton* repeatButton;
    QPushButton* randomButton;

    ProgressBarController* timeLine;
protected slots:
    void onPlayPauseButton();


};

#endif // CONTROLWIDGET_H
