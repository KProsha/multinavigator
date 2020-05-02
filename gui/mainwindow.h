#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QProcess>

#include "gui/centralwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void setState(AppGlobal::EAppState newState);

    void openDir(const QString& name);

    void onOpenDirAction();
    void onScanDirAction();

    void onGuiAction();

    void onEditTagsAction();

signals:
    void sigOpenDir(QString name);

    void sigNewStateAction(AppGlobal::EAppState state);

protected:
    CentralWidget* centralWidget;

    QToolBar* mainToolBar;

    QMenu* fileMenu;
    QAction* openDirAction;
    QAction* scanDirAction;

    QAction* showPlayListAction;
    QAction* createPlayList;
//    QAction* playCustomPlayList;
    QAction* showVideoAction;

    QAction* editTagsAction;

    void createActions();
    void createToolBar();
    void createConnections();
};

#endif // MAINWINDOW_H
