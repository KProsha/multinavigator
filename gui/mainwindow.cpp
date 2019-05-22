#include "mainwindow.h"

#include <QToolBar>
#include <QMenuBar>
#include <QWindow>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{

  options = new Options("config.ini",this);
  userOptions = new UserOptions("userconfig.ini",this);
  textValue = new TextValue("textvalue.ini", this);

  dataBase = new database::DataBase(this);

  centralWidgetI = new CentralWidget(this);

  FullScreen = false;

  setCentralWidget(centralWidgetI);

  createActions();
  createMenu();

  connect(centralWidgetI,&CentralWidget::sigSwitchFullScreen, this, &MainWindow::switchFullScreen);
  connect(centralWidgetI,&CentralWidget::sigNameOfPlaingMedia, this, &MainWindow::setWindowTitle);
  connect(database::DataBase::i, &database::DataBase::sigDirUpdateEvent,
          centralWidgetI->filterWidget,&FilterWidget::updateDirTag);

  if(!userOptions->getRecentDir().isEmpty()) sigOpenDir(userOptions->getRecentDir());

  resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  userOptions->save();
}
//------------------------------------------------------------------------------
void MainWindow::createActions()
{
    openDirAction = new QAction(TextValue::I->openDirectory());
    connect(openDirAction, &QAction::triggered, this, &MainWindow::onOpenDirAction);
    connect(this, &MainWindow::sigOpenDir, this, &MainWindow::openDir);
    connect(this, &MainWindow::sigOpenDir, centralWidgetI->filterWidget, &FilterWidget::setDirName);


}
//------------------------------------------------------------------------------
void MainWindow::createMenu()
{
  mainMenu = menuBar();
  fileMenu = mainMenu->addMenu(TextValue::I->file());
  fileMenu->addAction(openDirAction);

}
//------------------------------------------------------------------------------
void MainWindow::switchFullScreen()
{
  if(FullScreen){
    this->showNormal();
    this->showMaximized();
    centralWidgetI->setFullScreenMode(false);
    mainMenu->setVisible(true);

  }else {
    this->showFullScreen();
    centralWidgetI->setFullScreenMode(true);
    mainMenu->setVisible(false);

    //MainMenu->deleteLater();

    //this->setContentsMargins(0,0,0,0);


  }

  FullScreen = !FullScreen;
}
//------------------------------------------------------------------------------
void MainWindow::onOpenDirAction()
{
  QString Dir;

  if(userOptions->getRecentDir().isEmpty()){
    Dir = QApplication::applicationDirPath();
  }else{
    Dir = userOptions->getRecentDir();
  }

  QString DirName = QFileDialog::getExistingDirectory(this, TextValue::I->openDirectory(),
                                                      Dir,
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);

  emit sigOpenDir(DirName);
}
//------------------------------------------------------------------------------
void MainWindow::openDir(const QString& name)
{
  if(name.isEmpty() ) return;

  if(!dataBase->openDir(name)) return;

  userOptions->setRecentDir(name);
  dataBase->addRootDir(name);
}

