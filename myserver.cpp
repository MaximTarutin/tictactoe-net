#include "myserver.h"
#include <QDataStream>
#include <QDate>

MyServer::MyServer(QObject *parent)
    : QTcpServer{parent}
{
    init();
}

MyServer::~MyServer()
{

}

// ---------------------------------- Инициализация поля -----------------------------------

void MyServer::init()
{

}

// --------------------------- старт сервера ------------------------------

void MyServer::server_start()
{
    if(listen(QHostAddress::Any, 21111))
    {
        qDebug() << "Сервер запущен";
        connect(this, &QTcpServer::newConnection, this, &MyServer::new_connection);             // новое подключение

        int perviy_hod = rand()%2+0;            // случайно выбираем кто ходит первый
        if (perviy_hod==1)                      // Первым ходит компьютер
        {
            ACTIVE_PLAYER = "PLAYER_1";
        } else ACTIVE_PLAYER = "PLAYER_2";
        qDebug() << "Активный" << ACTIVE_PLAYER;
    } else
    {
        qDebug() << "Что-то пошло не так (((";
    }
}

// ------------------------------- Новое подключение ------------------------

void MyServer::new_connection()
{
    int num=0;
    static int i=0;
    i++;
    if(i>2) num=100;         // К серверу подключается не более 2-х клиентов, если 100 то выход

    QTcpSocket* t_socket = this->nextPendingConnection();

    clientura.append(t_socket);
    qDebug() << i << &clientura[0];
    connect(t_socket, &QTcpSocket::disconnected, t_socket, &QTcpSocket::deleteLater);       // потеря соединения
    connect(t_socket, &QTcpSocket::readyRead, this, &MyServer::get_data);                   // получаем данные от клиента

    QDataStream out(t_socket);
    out.setVersion(QDataStream::Qt_6_5);

    QString str=ACTIVE_PLAYER;
    out << num << str;              // Рассылаем клиентам код подключения (100 - откидывает 3-го клиента) и
                                    // имя активного игрока
}

// -------------------------------- Получаем данные и рассылаем всем игрокам -------------------------------

void MyServer::get_data()
{
    QTcpSocket* t_socket = (QTcpSocket*)sender();   // Получаем объект сокета, который вызвал данный слот

    QDataStream in(t_socket);
    in.setVersion(QDataStream::Qt_6_5);
    int num;
    QString str;
    in >> num >> str;                           // получаем данные из сокета
    qDebug() << num << "Активный" << str;

    if(num==200)
    {
        int perviy_hod = rand()%2+0;            // случайно выбираем кто ходит первый
        if (perviy_hod==1)                      // Первым ходит компьютер
        {
            str = "PLAYER_1";
        } else str = "PLAYER_2";
        qDebug() << "Новый активный игрок: " << str;
    }

    foreach (QTcpSocket *socket, clientura)     // Проходим по списку подключенных сокетов
    {
        QDataStream out(socket);
        out.setVersion(QDataStream::Qt_6_5);
        out << num << str;                      // отправляем всем данные
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
