#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include <QLabel>
#include <QTimer>
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
    SelectDialog    *select_dialog = nullptr;               // Диалог выбора сервер или клиент
    MyServer        *t_server = nullptr;                    // Сервер
    QTcpSocket      *t_socket = nullptr;                    // Сокет
    QString         PLAYER_NAME="";                         // Имя игрока
    QString         ACTIVE_PLAYER="";                       // Активный игрок
    QString         VICTORY_PLAYER="";                      // Выигравший игрок
    QString         IPSERVER="";                            // адрес сервера
    QLabel          *window_victory=nullptr;                // окно победы или поражения
    QTimer          *timer_victory=nullptr;                 // таймер показа окна победы
    int cell[10]={10,10,10,10,10,10,10,10,10,10};           // Клетки поля
    int score_player_1=0;                                   // счет игрока 1
    int score_player_2=0;                                   // счет игрока 2

    void check_to_victory();                                // Проверка на победу
    void victory(int i);                                    // Победа. i - номер победившего игрока
    void init();                                            // инициализация поля

private slots:
    void get_signal_select(QString s);                      // Получаем сигнал из диалога выбора (сервер или клиент)
    void start_server();                                    // стартуем как сервер
    void start_client();                                    // стартуем как клиент
    void get_data();                                        // получение данных от сервера
    void send_data(int num);                                // отправить данные на сервер
    void set_playing_field();                               // установить состояние клетки на поле
    void label_victory_hide();                              // скрыть сообщение о победе по истичении таймера
};
#endif // MAINWINDOW_H
