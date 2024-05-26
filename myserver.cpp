#include "myserver.h"

MyServer::MyServer(QObject *parent)
    : QTcpServer{parent}
{
    t_socket = new QTcpSocket();

    QString ip;
    QString ipAddress = my_ip_address();

    t_socket = new QTcpSocket();

    connect(this, &QTcpServer::newConnection, this, &MyServer::new_connection);           // новое подключение
}

MyServer::~MyServer()
{
    delete t_socket;
}

// --------------------------- старт сервера ------------------------------

void MyServer::server_start()
{
    if(listen(QHostAddress::Any, 21111))
    {
        qDebug() << "Сервер запущен";
        //exit(11);
    } else
    {
    }
}

// --------------------------------- Определяем свой ip ---------------------------------

QString MyServer::my_ip_address()
{
    QString ipAddress;
    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (const QHostAddress &entry : ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
            ipAddress = entry.toString();
            break;
        }
    }
    return ipAddress;
}

// ------------------------------- Новое подключение -----------------------------------

void MyServer::new_connection()
{
    t_socket = this->nextPendingConnection();                                                  // Сервер подключает свой сокет к клиентскому сокету
    connect(t_socket, &QTcpSocket::disconnected, this, &MyServer::end_connection);             // потеря соединения
    connect(t_socket, &QTcpSocket::readyRead,    this, &MyServer::get_data);                   // получаем данные от клиента
    qDebug() << "Соединение установлено";
}

// ------------------------------ Окончание соединения --------------------------------

void MyServer::end_connection()
{

}

// ------------------------------ Получение данных -----------------------------------

void MyServer::get_data()
{

}
