#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QMovie>
#include "myserver.h"
#include "selectdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    

private:
    SelectDialog    *select_dialog = nullptr;               // Диалог выбора сервер или клиент
    MyServer        *t_server = nullptr;                    // Сервер
    QTcpSocket      *t_socket = nullptr;                    // Сокет
    QString         PLAYER_NAME="";                         // Имя игрока
    QString         ACTIVE_PLAYER="";                       // Активный игрок
    QString         VICTORY_PLAYER="";                      // Выигравший игрок
    QString         IPSERVER="";                            // адрес сервера
    QLabel          *window_victory=nullptr;                // окно победы или поражения
    QLabel          *label_score_1=nullptr;                 // Счет 1 игрока
    QLabel          *label_score_2=nullptr;                 // Счет 2 игрока
    QLabel          *label_info=nullptr;                    // Информация чей ход
    QLabel          *sun=nullptr;                           // ничья
    QTimer          *timer_victory=nullptr;                 // таймер показа окна победы

    QPushButton     *pushButton_1=nullptr;
    QPushButton     *pushButton_2=nullptr;
    QPushButton     *pushButton_3=nullptr;
    QPushButton     *pushButton_4=nullptr;
    QPushButton     *pushButton_5=nullptr;                          // Ячейки поля
    QPushButton     *pushButton_6=nullptr;
    QPushButton     *pushButton_7=nullptr;
    QPushButton     *pushButton_8=nullptr;
    QPushButton     *pushButton_9=nullptr;

    QMovie          *movie_blue_ballon=nullptr;
    QMovie          *movie_green_ballon=nullptr;
    QMovie          *movie_sun=nullptr;
    QLabel          *blue_ballon=nullptr;
    QLabel          *green_ballon=nullptr;

    int cell[10]={10,10,10,10,10,10,10,10,10,10};           // Клетки поля
    int score_player_1=0;                                   // счет игрока 1
    int score_player_2=0;                                   // счет игрока 2

    void check_to_victory();                                // Проверка на победу
    void victory(int i);                                    // Победа. i - номер победившего игрока
    void init();                                            // инициализация поля
    int Screen_Width();                                     // возвращает ширину экрана
    int Screen_Height();                                    // возвращает высоту экрана

private slots:
    void get_signal_select(QString s);                      // Получаем сигнал из диалога выбора (сервер или клиент)
    void start_server();                                    // стартуем как сервер
    void start_client();                                    // стартуем как клиент
    void get_data();                                        // получение данных от сервера
    void send_data(int num);                                // отправить данные на сервер
    void set_playing_field();                               // установить состояние клетки на поле
    void label_victory_hide();                              // скрыть сообщение о победе по истичении таймера
    void show_field();                                      // прорисовка поля
};
#endif // MAINWINDOW_H
