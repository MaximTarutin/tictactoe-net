
/***********************************************
 *      Структура передачи и приема данных:    *
 * номер клетки-значение клетки-активный игрок *
 * *********************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);
    t_socket = new QTcpSocket(this);
    select_dialog = new SelectDialog(this);

    select_dialog->setWindowFlag(Qt::FramelessWindowHint);
    select_dialog->move(this->width()/2-select_dialog->width()/2,
                        this->height()/2-select_dialog->height()/2);

    ui->centralwidget->hide();
    select_dialog->show();

    connect(select_dialog, &SelectDialog::select_signal, this, &MainWindow::get_signal_select); // получаем сигнал из диалога
    connect(t_socket, &QTcpSocket::connected, this, &MainWindow::slot_connected);               // соединились с сервером
    connect(t_socket, &QTcpSocket::readyRead, this, &MainWindow::get_data);                     // получаем данные от сервера
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::set_playing_field);     // выбираем клетку
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::set_playing_field);
}

MainWindow::~MainWindow()
{
    delete t_server;
    delete ui;
}

// --------------------------- Получаем сигнал из диалога выбора ---------------------------

void MainWindow::get_signal_select(QString s)
{
    if(s=="server")
    {
        start_server();
        PLAYER_NAME="PLAYER_1";
    }
    if(s=="client")
    {
        start_client();
        PLAYER_NAME="PLAYER_2";
    }
}

// --------------------------- Запускаем сервер -------------------------------------------

void MainWindow::start_server()
{
    delete select_dialog;
    ui->centralwidget->show();
    t_server = new MyServer(this);
    t_server->server_start();
    QMessageBox::information(this, "Внимание!!!", "ip сервера: "+t_server->my_ip_address());
    t_socket->connectToHost(t_server->my_ip_address(), 21111);
}

// --------------------------- Запуск клиентской части -----------------------------------

void MainWindow::start_client()
{
    delete select_dialog;
    ui->centralwidget->show();
    QString IPSERVER = QInputDialog::getText(this,"ip адрес сервера","");   // Вводим ip-адрес сервера
    t_socket->connectToHost(IPSERVER, 21111);                               // Отправляем запрос на подключение к серверу
}

// -------------------------- Соединение установлено -------------------------------------

void MainWindow::slot_connected()

{
    ui->label->setText("Соединение установлено");
}

// ------------------------- Получение данных от сервера ---------------------------------

void MainWindow::get_data()
{
    QDataStream in(t_socket);
    in.setVersion(QDataStream::Qt_6_5);
    int num;
    QString str;
    in >> num >> str;

    ACTIVE_PLAYER = str;

    if(num==100) exit(100);
    switch(num)
    {
        case 1: ui->pushButton_1->setDisabled(true); ui->pushButton_1->setText("o"); break;
        case 2: ui->pushButton_2->setDisabled(true); ui->pushButton_2->setText("o"); break;
        case 3: ui->pushButton_3->setDisabled(true); ui->pushButton_3->setText("o"); break;
        case 4: ui->pushButton_4->setDisabled(true); ui->pushButton_4->setText("o"); break;
        case 5: ui->pushButton_5->setDisabled(true); ui->pushButton_5->setText("o"); break;
        case 6: ui->pushButton_6->setDisabled(true); ui->pushButton_6->setText("o"); break;
        case 7: ui->pushButton_7->setDisabled(true); ui->pushButton_7->setText("o"); break;
        case 8: ui->pushButton_8->setDisabled(true); ui->pushButton_8->setText("o"); break;
        case 9: ui->pushButton_9->setDisabled(true); ui->pushButton_9->setText("o"); break;
    }
}

// ------------------------ Отправка данных на сервер -----------------------------------

void MainWindow::send_data(int num)
{
    QString str;
    QDataStream out(t_socket);
    out.setVersion(QDataStream::Qt_6_5);
    if(ACTIVE_PLAYER!=PLAYER_NAME)
    {
        return;
    } else
    {
        if(PLAYER_NAME=="PLAYER_1") str="PLAYER_2"; else str="PLAYER_1";
        out << num << str;
    }
}

// ------------------------- Установитть состояние клетки на поле ------------------------

void MainWindow::set_playing_field()
{
    int num;
    if(QObject::sender()==ui->pushButton_1)
    {
        num=1;
    }
    if(QObject::sender()==ui->pushButton_2)
    {
        num=2;
    }
    if(QObject::sender()==ui->pushButton_3)
    {
        num=3;
    }
    if(QObject::sender()==ui->pushButton_4)
    {
        num=4;
    }
    if(QObject::sender()==ui->pushButton_5)
    {
        num=5;
    }
    if(QObject::sender()==ui->pushButton_6)
    {
        num=6;
    }
    if(QObject::sender()==ui->pushButton_7)
    {
        num=7;
    }
    if(QObject::sender()==ui->pushButton_8)
    {
        num=8;
    }
    if(QObject::sender()==ui->pushButton_9)
    {
        num=9;
    }

    send_data(num);
}
