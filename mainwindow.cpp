#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::send_data);

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
    QMessageBox::information(this, "Внимание!!!", "ip сервера: "+t_server->my_ip_address());
    t_server->server_start();
    t_socket->connectToHost(t_server->my_ip_address(), 21111);
}

// --------------------------- Запуск клиентской части -----------------------------------

void MainWindow::start_client()
{
    delete select_dialog;
    ui->centralwidget->show();
    QString IPSERVER = QInputDialog::getText(this,"ip адрес сервера","");
    t_socket->connectToHost(IPSERVER, 21111);              // Отправляем запрос на подключение к серверу
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
    if(num==0)
    {
        qDebug() << str;
        ui->label->setText(str);
    }

}

// ------------------------ Отправка данных на сервер -----------------------------------

void MainWindow::send_data()
{
    QDataStream out(t_socket);
    out.setVersion(QDataStream::Qt_6_5);
    int num=ui->lineEdit->text().toInt();
    QString str=PLAYER_NAME;
    out << num << str;
}
