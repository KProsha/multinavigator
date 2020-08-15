#include "mainwindow.h"

#include <QToolBar>
#include <QMenuBar>
#include <QWindow>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QActionGroup>

#include "backend/appglobal.h"

#include "scanoptionswidget.h"
#include "edittagdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new CentralWidget(this);

    setCentralWidget(centralWidget);

    createActions();
    createToolBar();
    createConnections();

    if(!AppGlobal::i()->getUserOptions()->getRecentDir().isEmpty())
        sigOpenDir(AppGlobal::i()->getUserOptions()->getRecentDir());

    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    showPlayListAction->trigger();
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    AppGlobal::i()->getUserOptions()->save();
}
//------------------------------------------------------------------------------
void MainWindow::createActions()
{
    openDirAction = new QAction(AppGlobal::i()->getTextValue("common/OpenDirectory"));
    scanDirAction = new QAction(AppGlobal::i()->getTextValue("common/ScanDirectory"));
    //-----  -----
    QActionGroup* stateActionGroup = new QActionGroup(this);
    showPlayListAction = stateActionGroup->addAction(AppGlobal::i()->getTextValue("common/showPlayList"));
    createPlayList  = stateActionGroup->addAction(AppGlobal::i()->getTextValue("common/createPlayList"));
//    playCustomPlayList = stateActionGroup->addAction(AppGlobal::i()->getTextValue("common/playCustomPlayList"));
    showVideoAction = stateActionGroup->addAction(AppGlobal::i()->getTextValue("common/showVideo"));

    showPlayListAction->setCheckable(true);
    createPlayList->setCheckable(true);
//    playCustomPlayList->setCheckable(true);
    showVideoAction->setCheckable(true);
    //-----  -----
    editTagsAction = new QAction(AppGlobal::i()->getTextValue("tag/Edit"));
}
//------------------------------------------------------------------------------
void MainWindow::createToolBar()
{
    mainToolBar = this->addToolBar("");
    mainToolBar->addAction(openDirAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(scanDirAction);
    mainToolBar->addSeparator();

    mainToolBar->addAction(showPlayListAction);
    mainToolBar->addAction(createPlayList);
//    mainToolBar->addAction(playCustomPlayList);
    mainToolBar->addAction(showVideoAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(editTagsAction);

}
//------------------------------------------------------------------------------
void MainWindow::createConnections()
{
    connect(centralWidget,&CentralWidget::sigNameOfPlaingMedia, this, &MainWindow::setWindowTitle);

    connect(openDirAction, &QAction::triggered, this, &MainWindow::onOpenDirAction);
    connect(scanDirAction, &QAction::triggered, this, &MainWindow::onScanDirAction);
    connect(this, &MainWindow::sigOpenDir, this, &MainWindow::openDir);

    connect(showVideoAction, &QAction::triggered, this, &MainWindow::onGuiAction);
    connect(showPlayListAction, &QAction::triggered, this, &MainWindow::onGuiAction);
//    connect(playCustomPlayList, &QAction::triggered, this, &MainWindow::onGuiAction);
    connect(createPlayList, &QAction::triggered, this, &MainWindow::onGuiAction);

    connect(editTagsAction, &QAction::triggered, this, &MainWindow::onEditTagsAction);

    connect(this, &MainWindow::sigNewStateAction, AppGlobal::i(), &AppGlobal::setNewState);
    connect(AppGlobal::i(), &AppGlobal::sigNewState, this, &MainWindow::setState);
}
//------------------------------------------------------------------------------
void MainWindow::setState(AppGlobal::EAppState newState)
{
    if(newState != AppGlobal::StateFullScreen){
        if(this->isFullScreen()){
            this->showNormal();
            this->showMaximized();
            mainToolBar->setVisible(true);
        }
    }else {
        this->showFullScreen();
        mainToolBar->setVisible(false);
    }
}
//------------------------------------------------------------------------------
void MainWindow::onOpenDirAction()
{
    QString Dir;

    if(AppGlobal::i()->getUserOptions()->getRecentDir().isEmpty()){
        Dir = QApplication::applicationDirPath();
    }else{
        Dir = AppGlobal::i()->getUserOptions()->getRecentDir();
    }

    QString DirName = QFileDialog::getExistingDirectory(this, AppGlobal::i()->getTextValue("common/OpenDirectory"),
                                                        Dir,
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

    emit sigOpenDir(DirName);
}
//------------------------------------------------------------------------------
void MainWindow::onScanDirAction()
{
    ScanOptionsWidget scanOptionsWidget;

    if(!scanOptionsWidget.exec()) return;

    AppGlobal::i()->scanRootDir();
    //openDir(AppGlobal::i()->getRootDirPath());
}
//------------------------------------------------------------------------------
void MainWindow::onGuiAction()
{
    if(showPlayListAction == sender()){
        emit sigNewStateAction(AppGlobal::StatePlayList);
        return;
    }
    if(createPlayList == sender()){
        emit sigNewStateAction(AppGlobal::StateCreatePlayList);
        return;
    }
//    if(playCustomPlayList == sender()){
//        emit sigNewStateAction(AppGlobal::StatePlayCustomPlayList);
//        return;
//    }
    if(showVideoAction == sender()){
        emit sigNewStateAction(AppGlobal::StateVideo);
        return;
    }
}
//------------------------------------------------------------------------------
void MainWindow::onEditTagsAction()
{
    EditTagDialog scanOptionsWidget;
    scanOptionsWidget.showMaximized();

    scanOptionsWidget.exec();
}
//------------------------------------------------------------------------------
void MainWindow::openDir(const QString& name)
{
    if(name.isEmpty() ) return;

    if(!AppGlobal::i()->getDataBase()->openDir(name)) return;
    AppGlobal::i()->setRootDirPath(name);

    setWindowTitle(name);
    AppGlobal::i()->getUserOptions()->setRecentDir(name);
}

