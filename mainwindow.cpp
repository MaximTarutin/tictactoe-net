#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpServer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t_server = new MyServer();
    t_socket = new QTcpSocket();

    while (NAME_PLAYER=="")
    {
        NAME_PLAYER = QInputDialog::getText(this,"Имя","Как Ваше имя ?");
    }

    connect(ui->pushButton_server, &QPushButton::clicked, this, &MainWindow::start_server);
    connect(ui->pushButton_client, &QPushButton::clicked, this, &MainWindow::start_client);
    connect(t_socket, &QTcpSocket::connected, this, &MainWindow::begin_connect);

}

MainWindow::~MainWindow()
{
    delete t_socket;
    delete t_server;
    delete ui;
}

// ------------------------------------ инициализация -------------------------------------

void MainWindow::init()
{
    //----------------------------
}

// ----------------------------------- Запускаем сервер -----------------------------------

void MainWindow::start_server()
{
    t_server->server_start();
    IPSERVER = t_server->my_ip_address();
    QMessageBox::information(this, "Внимание!!!", "ip сервера: "+IPSERVER);
    emit ip_server(IPSERVER);
    t_socket->connectToHost(IPSERVER, 21111);              // Отправляем запрос на подключение к серверу
    ui->pushButton_server->hide();
    ui->pushButton_client->hide();
}

// ----------------------------------- Подключение клиента к серверу ----------------------

void MainWindow::start_client()
{
    IPSERVER = QInputDialog::getText(this,"ip адрес сервера","");
    emit ip_server(IPSERVER);
    t_socket->connectToHost(IPSERVER, 21111);              // Отправляем запрос на подключение к серверу
    ui->pushButton_server->hide();
    ui->pushButton_client->hide();
}

// ---------------------------------- Соединение установлено -----------------------------

void MainWindow::begin_connect()
{
    ui->label->setText("Соединение установлено");
}
