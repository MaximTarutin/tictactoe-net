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

}

// ------------------------------- Новое подключение ------------------------

void MyServer::new_connection()
{

}

// -------------------------------- Получаем данные и рассылаем всем игрокам -------------------------------

void MyServer::get_data()
{

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
