#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QProcess>

#include "gui/centralwidget.h"
#include "database/database.h"
#include "options/options.h"
#include "options/useroptions.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  Options* options;
  UserOptions* userOptions;
  TextValue* textValue;
  // -----  -----
  database::DataBase* dataBase;

  // -----  -----
  bool FullScreen;
  CentralWidget* centralWidgetI;

  QToolBar* mainToolBar;

  QMenuBar* mainMenu;
  QMenu* fileMenu;
  QAction* openDirAction;

  void createActions();
  void createMenu();
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

protected slots:
  void switchFullScreen();

  void openDir(const QString& name);

  void onOpenDirAction();

signals:
  void sigOpenDir(QString name);



};

#endif // MAINWINDOW_H
