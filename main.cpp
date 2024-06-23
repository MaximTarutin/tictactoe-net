
#include "mainwindow.h"
#include <QApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyServer server;
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
