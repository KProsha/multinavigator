#include "controlwidget.h"

#include <QHBoxLayout>
#include <QStyle>
#include <QIcon>
#include <QApplication>

#include "backend/appglobal.h"

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    QSizePolicy smallIconSizePolicy(QSizePolicy::Maximum,
                                    QSizePolicy::Fixed,
                                    QSizePolicy::ToolButton);

    playPauseButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay)),"" , this);
    backwardButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaSkipBackward)),"" , this);
    stopButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaStop)),"" , this);
    forwardButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaSkipForward)),"" , this);

    repeatButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_BrowserReload)),"" , this);
    randomButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaSeekForward)),"" , this);

    timeLine = new ProgressBarController(this);
    timeLine->setTextVisible(false);
    // -----  -----
    playPauseButton->setToolTip(AppGlobal::i()->getTextValue("control/Play"));
    backwardButton->setToolTip(AppGlobal::i()->getTextValue("control/Backward"));
    stopButton->setToolTip(AppGlobal::i()->getTextValue("control/Stop"));
    forwardButton->setToolTip(AppGlobal::i()->getTextValue("control/Forward"));

    repeatButton->setToolTip(AppGlobal::i()->getTextValue("control/Repeat"));
    randomButton->setToolTip(AppGlobal::i()->getTextValue("control/Random"));
    // -----  -----
    playPauseButton->setSizePolicy(smallIconSizePolicy);
    backwardButton->setSizePolicy(smallIconSizePolicy);
    stopButton->setSizePolicy(smallIconSizePolicy);
    forwardButton->setSizePolicy(smallIconSizePolicy);

    repeatButton->setSizePolicy(smallIconSizePolicy);
    randomButton->setSizePolicy(smallIconSizePolicy);

    timeLine->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    // -----  -----
    repeatButton->setCheckable(true);
    randomButton->setCheckable(true);
    // -----  -----
    auto mainLayout = new QHBoxLayout();
    setLayout(mainLayout);

    mainLayout->addWidget(playPauseButton);
    mainLayout->addWidget(backwardButton);
    mainLayout->addWidget(stopButton);
    mainLayout->addWidget(forwardButton);
    mainLayout->addWidget(repeatButton);
    mainLayout->addWidget(randomButton);
    mainLayout->addWidget(timeLine);

    connect(timeLine, &ProgressBarController::sigSetPosEvent, this, &ControlWidget::sigSetPosEvent);
    connect(playPauseButton, &QPushButton::clicked, this, &ControlWidget::onPlayPauseButton);
    connect(stopButton, &QPushButton::clicked, this, &ControlWidget::sigStop);

    connect(randomButton, &QPushButton::clicked, AppGlobal::i(), &AppGlobal::toggleRandomMode);
    connect(repeatButton, &QPushButton::clicked, AppGlobal::i(), &AppGlobal::toggleRepeatMode);
    connect(AppGlobal::i(), &AppGlobal::sigNewRandomMode, randomButton, &QPushButton::setChecked);
    connect(AppGlobal::i(), &AppGlobal::sigNewRepeatMode, repeatButton, &QPushButton::setChecked);

    connect(forwardButton, &QPushButton::clicked, AppGlobal::i(), &AppGlobal::moveForward);
    connect(backwardButton, &QPushButton::clicked, AppGlobal::i(), &AppGlobal::moveBackward);


}
//------------------------------------------------------------------------------
void ControlWidget::setState(ControlWidget::EState newState)
{
    state = newState;
    switch (newState) {
    case StateStopped:
        playPauseButton->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay)));
        playPauseButton->setToolTip(AppGlobal::i()->getTextValue("control/Play"));
        break;
    case StatePlaying:
        playPauseButton->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause)));
        playPauseButton->setToolTip(AppGlobal::i()->getTextValue("control/Pause"));
        break;
    case StatePaused:
        playPauseButton->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay)));
        playPauseButton->setToolTip(AppGlobal::i()->getTextValue("control/Play"));
        break;
    }
}
//------------------------------------------------------------------------------
void ControlWidget::setTimeLinePos(quint64 pos)
{
    timeLine->setValue(static_cast<int>(pos));
}
//------------------------------------------------------------------------------
void ControlWidget::setDuration(quint64 duration)
{
    timeLine->setMaximum(static_cast<int>(duration));
}
//------------------------------------------------------------------------------
void ControlWidget::onMediaPlayerStateChanged(QMediaPlayer::State state)
{
    switch (state) {
    case QMediaPlayer::StoppedState:
        setState(StateStopped);
        break;
    case QMediaPlayer::PlayingState:
        setState(StatePlaying);
        break;
    case QMediaPlayer::PausedState:
        setState(StatePaused);
        break;
    }
}
//------------------------------------------------------------------------------
void ControlWidget::onPlayPauseButton()
{
    switch (state) {
    case StatePlaying:
        emit sigPause();
        break;
    case StateStopped:
    case StatePaused:
        emit sigPlay();
        break;
    }
}



