#include "myserver.h"
#include <QDataStream>
#include <QDate>
#include <QRegularExpression>

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

        // int perviy_hod = rand()%2+0;            // случайно выбираем кто ходит первый
        // if (perviy_hod==1)                      // Первым ходит компьютер
        // {
        //     ACTIVE_PLAYER = "PLAYER_1";
        // } else ACTIVE_PLAYER = "PLAYER_2";
        // qDebug() << "Активный" << ACTIVE_PLAYER;
    } else
    {
        qDebug() << "Что-то пошло не так (((";
    }
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

// ---------------------- Проверка занятости порта в локальной сети --------------------------------

bool MyServer::chek_port(int port)
{
    QTcpSocket *soket = new QTcpSocket(this);
    QString ip;
    QString myAddress = my_ip_address();
    QStringList strList = myAddress.split(QRegularExpression("[.]"), Qt::SkipEmptyParts);

    int n0 = strList[0].toInt();
    int n1 = strList[1].toInt();
    int n2 = strList[2].toInt();
    int n3 = strList[3].toInt();

    QString ip0 = QString::number(n0)+"."+QString::number(n1)+"."+QString::number(n2)+".";

    for(int i=n3; i<=255; ++i)
    {
        ip = ip0+QString::number(i);
        soket->disconnectFromHost();
        soket->connectToHost(ip, port);
        if (soket->waitForConnected(10))
        {
            delete soket;                       // Порт уже занят
            return false;
        }
    }
    delete soket;
    return true;
}
