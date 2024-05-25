#include "myserver.h"

MyServer::MyServer(QObject *parent)
    : QTcpServer{parent}
{
    t_socket = new QTcpSocket();

    QString ip;
    QString ipAddress = my_ip_address();
}

MyServer::~MyServer()
{

}

// --------------------------- старт сервера ------------------------------

void MyServer::server_start()
{
    if(!listen(QHostAddress::Any, 21111))
    {
        qDebug() << "Сервер запущен";
        exit(11);
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
