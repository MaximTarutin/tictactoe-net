#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include "myserver.h"
#include "selectdialog.h"

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
    SelectDialog    *select_dialog = nullptr;
    MyServer        *t_server = nullptr;
    QTcpSocket      *t_socket = nullptr;
    QString         PLAYER_NAME="";

private slots:
    void get_signal_select(QString s);                      // Получаем сигнал из диалога выбора (сервер или клиент)
    void start_server();                                    // стартуем как сервер
    void start_client();                                    // стартуем как клиент
    void slot_connected();                                  // соединение установлено
    void get_data();                                        // получение данных от сервера
    void send_data(int num);                                // отправить данные на сервер
    void set_playing_field();                               // установить состояние клетки на поле
};
#endif // MAINWINDOW_H
