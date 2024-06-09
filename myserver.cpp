#include "myserver.h"
#include <QDataStream>
#include <QDate>

MyServer::MyServer(QObject *parent)
    : QTcpServer{parent}
{

}

MyServer::~MyServer()
{

}

// --------------------------- старт сервера ------------------------------

void MyServer::server_start()
{
    if(listen(QHostAddress::Any, 21111))
    {
        qDebug() << "Сервер запущен";
        connect(this, &QTcpServer::newConnection, this, &MyServer::new_connection);             // новое подключение

    } else
    {
        qDebug() << "Что-то пошло не так (((";
    }
}

// ------------------------------- Новое подключение ------------------------

void MyServer::new_connection()
{
    QTcpSocket* t_socket = this->nextPendingConnection();

    connect(t_socket, &QTcpSocket::disconnected, t_socket, &QTcpSocket::deleteLater);       // потеря соединения
    connect(t_socket, &QTcpSocket::readyRead, this, &MyServer::get_data);                   // получаем данные от клиента

    QDataStream out(t_socket);
    out.setVersion(QDataStream::Qt_6_5);

    int num=0;
    QString str="Сервер ответил: Соединение установлено";

    out << num << str;

    qDebug() << "Соединение установлено !!!";
}

// -------------------------------- Получаем данные -------------------------------------

void MyServer::get_data()
{
    qDebug() << "прием";
    QTcpSocket* t_socket = (QTcpSocket*)sender();
    QDataStream in(t_socket);
    in.setVersion(QDataStream::Qt_6_5);
    int num;
    QString str;
    in >> num >> str;
    qDebug() << num << str;
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
