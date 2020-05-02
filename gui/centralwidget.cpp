#include "centralwidget.h"

#include <QMouseEvent>
#include <QSplitter>
//#include <QVBoxLayout>
#include <QFileInfo>

#include "backend/playlistmodel.h"

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    videoWidget = new VideoWidget(this);
    playlistWidget = new PlaylistWidget(this);
    fileTagListWidget = new FileTagListWidget(this);
    playListTagWidget = new PlayListTagWidget(this);
    controlWidget = new ControlWidget(this);

    hideControlTimer = new QTimer(this);
    hideControlTimer->setInterval(5000);
    hideControlTimer->setSingleShot(true);

    // ----- -----
    player = new QMediaPlayer(this,QMediaPlayer::VideoSurface);
    player->setVideoOutput(videoWidget);

    // ----- -----
    QSplitter* splitter = new QSplitter(Qt::Horizontal,this);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    splitter->addWidget(videoWidget);
    splitter->addWidget(playlistWidget);
    splitter->addWidget(fileTagListWidget);
    splitter->addWidget(playListTagWidget);

    splitter->setSizes({200,200,100,100});

    auto mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(splitter);
    mainLayout->addWidget(controlWidget);

    setLayout(mainLayout);
    // ----- -----
    connect(videoWidget, &VideoWidget::sigMouseDoubleClick, AppGlobal::i(), &AppGlobal::switchFullScreen);
    connect(AppGlobal::i(), &AppGlobal::sigNewCurrentFile, this, &CentralWidget::playFile);

    connect(AppGlobal::i(), &AppGlobal::sigNewState, this, &CentralWidget::setState);

    connect(videoWidget, &VideoWidget::sigMousePressedInFullScreen,
            hideControlTimer,static_cast<void (QTimer:: *)()>( &QTimer::start));
    connect(hideControlTimer, &QTimer::timeout, controlWidget, &ControlWidget::hide);
    connect(videoWidget, &VideoWidget::sigMousePressedInFullScreen, controlWidget, &ControlWidget::show);

    connect(playListTagWidget, &PlayListTagWidget::sigTagSelected, AppGlobal::i(), &AppGlobal::setFilterTagIdList);

    // -----  -----
    connect(controlWidget, &ControlWidget::sigSetPosEvent,  player, &QMediaPlayer::setPosition);
    connect(controlWidget, &ControlWidget::sigPlay,  player, &QMediaPlayer::play);
    connect(controlWidget, &ControlWidget::sigStop,  player, &QMediaPlayer::stop);
    connect(controlWidget, &ControlWidget::sigPause,  player, &QMediaPlayer::pause);

    connect(player, &QMediaPlayer::positionChanged, controlWidget, &ControlWidget::setTimeLinePos);
    connect(player, &QMediaPlayer::durationChanged, controlWidget, &ControlWidget::setDuration);
    connect(player, &QMediaPlayer::stateChanged, controlWidget, &ControlWidget::onMediaPlayerStateChanged);
    // -----  -----

}
//------------------------------------------------------------------------------
void CentralWidget::playFile()
{
    QString name = AppGlobal::i()->getDataBase()->getFilePath(AppGlobal::i()->getCurrentFileId());

    QFileInfo fileInfo(name);
    if(!fileInfo.exists()) return;

    QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());

    player->setMedia(url);
    player->play();
    emit(sigNameOfPlaingMedia(name));
}
//------------------------------------------------------------------------------
void CentralWidget::setState(AppGlobal::EAppState newState)
{
    switch (newState) {
    // -----  -----
    case AppGlobal::StateFullScreen:{
        fileTagListWidget->setVisible(false);
        playListTagWidget->setVisible(false);
        playlistWidget->setVisible(false);        
        controlWidget->setVisible(false);
    }break;
        // -----  -----
    case AppGlobal::StatePlayList:{        
        fileTagListWidget->setVisible(true);
        playListTagWidget->setVisible(false);
        playlistWidget->setVisible(true);
        controlWidget->setVisible(true);

        AppGlobal::i()->setCurrentAllPlayListModel();
    }break;
        // -----  -----
    case AppGlobal::StateCreatePlayList:{        
        fileTagListWidget->setVisible(true);
        playListTagWidget->setVisible(true);
        playlistWidget->setVisible(true);
        controlWidget->setVisible(true);

        AppGlobal::i()->setCurrentCustomPlayListModel();
    }break;
        // -----  -----
    case AppGlobal::StateVideo:{
        playListTagWidget->setVisible(false);
        fileTagListWidget->setVisible(false);
        playlistWidget->setVisible(false);
        controlWidget->setVisible(false);
    }break;
    }
}
//------------------------------------------------------------------------------

