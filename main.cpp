
#include <QApplication>

#include "gui/mainwindow.h"
#include "backend/appglobal.h"


int main(int argc, char *argv[])
{
    AppGlobal appGlobal;

    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
