
#include "mainwindow.h"
#include <QApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyServer server;
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
