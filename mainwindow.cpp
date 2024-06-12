
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
    //t_server = new MyServer(this);
    select_dialog = new SelectDialog(this);
    information_message = new QMessageBox(this);

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
    delete information_message;
    delete t_server;
    delete ui;
}

// ----------------------------------- Инициализация поля ----------------------------------

void MainWindow::init()
{
    for(int i=0; i<10; i++)
    {
        cell[i]=10;                     // приводим массив в первоначальное состояние
    }
    ui->pushButton_1->setText("");
    ui->pushButton_2->setText("");
    ui->pushButton_3->setText("");
    ui->pushButton_4->setText("");
    ui->pushButton_5->setText("");
    ui->pushButton_6->setText("");
    ui->pushButton_7->setText("");
    ui->pushButton_8->setText("");
    ui->pushButton_9->setText("");
    ui->pushButton_1->setEnabled(true); // Очищаем поле
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_9->setEnabled(true);

    QDataStream out(t_socket);
    out.setVersion(QDataStream::Qt_6_5);
    out << 0 << "";
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
    IPSERVER = QInputDialog::getText(this,"ip адрес сервера","");           // Вводим ip-адрес сервера
    t_socket->connectToHost(IPSERVER, 21111);                               // Отправляем запрос на подключение к серверу
}

// -------------------------- Соединение установлено -------------------------------------

void MainWindow::slot_connected()

{

}

// ------------------------- Получение данных от сервера ---------------------------------

void MainWindow::get_data()
{
    QDataStream in(t_socket);
    in.setVersion(QDataStream::Qt_6_5);
    int num;
    QString str;
    QString ox;             // Времянка
    in >> num >> str;

    ACTIVE_PLAYER = str;

    if(ACTIVE_PLAYER==PLAYER_NAME)
    {
        ui->label_info->setText("ВАШ ХОД !!!");
    } else
    {
        ui->label_info->setText("Ход противника");
    }

    if(ACTIVE_PLAYER=="PLAYER_1")
    {
        ox="x";
        cell[num]=1;
    } else
    {
        cell[num]=2;
        ox="0";
    }
    if(num==0)
    {
        information_message->hide();
        return;
    }
    if(num==100) exit(100);
    switch(num)
    {
        case 1: ui->pushButton_1->setDisabled(true);
                ui->pushButton_1->setText(ox);
                break;
        case 2: ui->pushButton_2->setDisabled(true);
                ui->pushButton_2->setText(ox);
                break;
        case 3: ui->pushButton_3->setDisabled(true);
                ui->pushButton_3->setText(ox);
                break;
        case 4: ui->pushButton_4->setDisabled(true);
                ui->pushButton_4->setText(ox);
                break;
        case 5: ui->pushButton_5->setDisabled(true);
                ui->pushButton_5->setText(ox);
                break;
        case 6: ui->pushButton_6->setDisabled(true);
                ui->pushButton_6->setText(ox);
                break;
        case 7: ui->pushButton_7->setDisabled(true);
                ui->pushButton_7->setText(ox);
                break;
        case 8: ui->pushButton_8->setDisabled(true);
                ui->pushButton_8->setText(ox);
                break;
        case 9: ui->pushButton_9->setDisabled(true);
                ui->pushButton_9->setText(ox);
                break;
    }

        check_to_victory();
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
    int num1=0;
    if(QObject::sender()==ui->pushButton_1)
    {
        num1=1;
    }
    if(QObject::sender()==ui->pushButton_2)
    {
        num1=2;
    }
    if(QObject::sender()==ui->pushButton_3)
    {
        num1=3;
    }
    if(QObject::sender()==ui->pushButton_4)
    {
        num1=4;
    }
    if(QObject::sender()==ui->pushButton_5)
    {
        num1=5;
    }
    if(QObject::sender()==ui->pushButton_6)
    {
        num1=6;
    }
    if(QObject::sender()==ui->pushButton_7)
    {
        num1=7;
    }
    if(QObject::sender()==ui->pushButton_8)
    {
        num1=8;
    }
    if(QObject::sender()==ui->pushButton_9)
    {
        num1=9;
    }
    send_data(num1);
}

// --------------------------------- Проверка на победу --------------------------------

void MainWindow::check_to_victory()
{
    int col1 = cell[1]+cell[2]+cell[3];
    int col2 = cell[4]+cell[5]+cell[6];
    int col3 = cell[7]+cell[8]+cell[9];
    int row1 = cell[1]+cell[4]+cell[7];
    int row2 = cell[2]+cell[5]+cell[8];
    int row3 = cell[3]+cell[6]+cell[9];
    int diag1 = cell[1]+cell[5]+cell[9];
    int diag2 = cell[3]+cell[5]+cell[7];

    if((col1==3)or(col2==3)or(col3==3)or
       (row1==3)or(row2==3)or(row3==3)or
        (diag1==3)or(diag2==3)) victory(2);

    if((col1==6)or(col2==6)or(col3==6)or
       (row1==6)or(row2==6)or(row3==6)or
        (diag1==6)or(diag2==6)) victory(1);
}

// --------------------------------------- Победа ------------------------------------------

void MainWindow::victory(int i)
{
    if(i==1) score_player_1++;
        else score_player_2++;
        information_message->setInformativeText("Победа !!!!");
        information_message->setText("Победил игрок "+QString::number(i));
        information_message->setModal(true);
        information_message->exec();
    init();
}
