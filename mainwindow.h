#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include "myserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    MyServer        *t_server;
    QTcpSocket      *t_socket;

    QString IPSERVER;
    QString NAME_PLAYER;

    void init();

private slots:
    void start_server();
    void start_client();
    void begin_connect();

signals:
    void ip_server(QString ip);             // передаем сигнал ip сервера
};
#endif // MAINWINDOW_H
