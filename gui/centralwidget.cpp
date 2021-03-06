#include "centralwidget.h"

#include <QMouseEvent>
#include <QSplitter>
#include <QFileInfo>

#include "backend/playlistmodel.h"

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    videoWidget = new VideoWidget(this);
    playlistWidget = new PlaylistWidget(this);
    fileTagListWidget = new TagListWidget<FileTagGroupWidget>(this);
    playListTagWidget = new TagListWidget<PlayListTagGroupWidget>(this);
    controlWidget = new ControlWidget(this);

    hideControlTimer = new QTimer(this);
    hideControlTimer->setInterval(5000);
    hideControlTimer->setSingleShot(true);

    // ----- -----
    player = new QMediaPlayer(this,QMediaPlayer::VideoSurface);
    player->setVideoOutput(videoWidget);
    controlWidget->setPlayer(player);

    // ----- -----
    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal,this);
    mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QSplitter* videoPlaylistSplitter = new QSplitter(Qt::Vertical,this);
    videoPlaylistSplitter->addWidget(videoWidget);
    videoPlaylistSplitter->addWidget(playlistWidget);
    videoPlaylistSplitter->setSizes({50,50});

    mainSplitter->addWidget(fileTagListWidget);
    mainSplitter->addWidget(videoPlaylistSplitter);
    mainSplitter->addWidget(playListTagWidget);

    mainSplitter->setSizes({100,400,100});

    auto mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(mainSplitter);
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
        hideControlTimer->stop();

        AppGlobal::i()->setCurrentAllPlayListModel();
    }break;
        // -----  -----
    case AppGlobal::StateCreatePlayList:{
        fileTagListWidget->setVisible(true);
        playListTagWidget->setVisible(true);
        playlistWidget->setVisible(true);
        controlWidget->setVisible(true);
        hideControlTimer->stop();
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

