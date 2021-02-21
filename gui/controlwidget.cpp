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

    muted = false;

    playPauseButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay)),"" , this);
    backwardButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaSkipBackward)),"" , this);
    stopButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaStop)),"" , this);
    forwardButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaSkipForward)),"" , this);

    repeatButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_BrowserReload)),"" , this);
    randomButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaSeekForward)),"" , this);

    timeLine = new ProgressBarController(this);
    timeLine->setTextVisible(false);

    muteButton = new QPushButton(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaVolume)),"" , this);
    volumeLevel = new ProgressBarController(this);
    volumeLevel->setTextVisible(false);
    volumeLevel->setMaximum(100);
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

    muteButton->setSizePolicy(smallIconSizePolicy);
    volumeLevel->setSizePolicy(smallIconSizePolicy);

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
    mainLayout->addWidget(muteButton);
    mainLayout->addWidget(volumeLevel);

    connect(timeLine, &ProgressBarController::sigSetPosEvent, this, &ControlWidget::sigSetPosEvent);
    connect(playPauseButton, &QPushButton::clicked, this, &ControlWidget::onPlayPauseButton);
    connect(stopButton, &QPushButton::clicked, this, &ControlWidget::sigStop);

    connect(muteButton, &QPushButton::clicked, this, &ControlWidget::onMuteButton);

    connect(randomButton, &QPushButton::clicked, AppGlobal::i(), &AppGlobal::toggleRandomMode);
    connect(repeatButton, &QPushButton::clicked, AppGlobal::i(), &AppGlobal::toggleRepeatMode);
//    connect(AppGlobal::i(), &AppGlobal::sigNewRandomMode, randomButton, &QPushButton::setChecked);
    connect(AppGlobal::i(), &AppGlobal::sigNewRepeatMode, repeatButton, &QPushButton::setChecked);

    connect(forwardButton, &QPushButton::clicked, AppGlobal::i(), &AppGlobal::moveForward);
    connect(backwardButton, &QPushButton::clicked, AppGlobal::i(), &AppGlobal::moveBackward);
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
void ControlWidget::onMediaPlayerStateChanged(QMediaPlayer::State newState)
{
    state = newState;
    switch (newState) {
    case QMediaPlayer::StoppedState:
        playPauseButton->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay)));
        playPauseButton->setToolTip(AppGlobal::i()->getTextValue("control/Play"));
        break;
    case QMediaPlayer::PlayingState:
        playPauseButton->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause)));
        playPauseButton->setToolTip(AppGlobal::i()->getTextValue("control/Pause"));
        break;
    case QMediaPlayer::PausedState:
        playPauseButton->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay)));
        playPauseButton->setToolTip(AppGlobal::i()->getTextValue("control/Play"));
        break;
    }
}
//------------------------------------------------------------------------------
void ControlWidget::onMediaPlayerMutedChanged(bool value)
{
    muted = value;
    if(value == true)
        muteButton->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaVolumeMuted)));
    else
        muteButton->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaVolume)));
}
//------------------------------------------------------------------------------
void ControlWidget::onMuteButton()
{
    if(muted)
        emit sigMute(false);
    else
        emit sigMute(true);
}
//------------------------------------------------------------------------------
void ControlWidget::setPlayer(QMediaPlayer* value)
{
    player = value;
    connect(this, &ControlWidget::sigSetPosEvent,  player, &QMediaPlayer::setPosition);
    connect(this, &ControlWidget::sigPlay,  player, &QMediaPlayer::play);
    connect(this, &ControlWidget::sigStop,  player, &QMediaPlayer::stop);
    connect(this, &ControlWidget::sigPause,  player, &QMediaPlayer::pause);
    connect(this, &ControlWidget::sigMute,  player, &QMediaPlayer::setMuted);
    connect(volumeLevel, &ProgressBarController::sigSetPosEvent,  player, &QMediaPlayer::setVolume);

    connect(player, &QMediaPlayer::positionChanged, this, &ControlWidget::setTimeLinePos);
    connect(player, &QMediaPlayer::durationChanged, this, &ControlWidget::setDuration);
    connect(player, &QMediaPlayer::stateChanged, this, &ControlWidget::onMediaPlayerStateChanged);
    connect(player, &QMediaPlayer::mutedChanged, this, &ControlWidget::onMediaPlayerMutedChanged);
    connect(player, &QMediaPlayer::volumeChanged, volumeLevel, &ProgressBarController::setValue);

    volumeLevel->setValue(player->volume());
}
//------------------------------------------------------------------------------
void ControlWidget::onPlayPauseButton()
{
    switch (state) {
    case QMediaPlayer::PlayingState:
        emit sigPause();
        break;
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
        emit sigPlay();
        break;
    }
}



