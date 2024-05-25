#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpServer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t_server = new MyServer();

    connect(ui->pushButton_server, &QPushButton::clicked, this, &MainWindow::start_server);
    connect(ui->pushButton_client, &QPushButton::clicked, this, &MainWindow::connect_client_to_server);
}

MainWindow::~MainWindow()
{
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
    qDebug() << IPSERVER;
    QMessageBox::information(this, "Внимание!!!", "ip сервера: "+IPSERVER);
    ui->pushButton_server->hide();
    ui->pushButton_client->hide();
}

// ----------------------------------- Подключение клиента к серверу ----------------------

void MainWindow::connect_client_to_server()
{
    IPSERVER = QInputDialog::getText(this,"ip адрес сервера","");
    ui->pushButton_server->hide();
    ui->pushButton_client->hide();
}
