#include "myserver.h"
#include <QDataStream>
#include <QDate>

MyServer::MyServer(QObject *parent)
    : QTcpServer{parent}
{
    //t_socket = new QTcpSocket();

    //QString ip;
    //QString ipAddress = my_ip_address();

    setMaxPendingConnections(2);        // Устанавливаем максимальное количество подключений 2

    //connect(t_socket, &QTcpSocket::readyRead, this, &MyServer::get_data);                   // получение данных от клиента
}

MyServer::~MyServer()
{
    //delete t_socket;
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
    QTcpSocket* t_socket = this->nextPendingConnection();

    connect(t_socket, &QTcpSocket::disconnected, t_socket, &QTcpSocket::deleteLater);
    connect(t_socket, &QTcpSocket::readyRead, this, &MyServer::get_data);

    sendToClient(t_socket, 0, "Server Response: Connected!");
}

// -------------------------------- Получаем данные -------------------------------------

void MyServer::get_data()
{
    QTcpSocket* t_socket = (QTcpSocket*)sender();
    // QHostAddress addr=t_socket->peerAddress();
    QDataStream in(t_socket);
    in.setVersion(QDataStream::Qt_6_5);

    for (;;)        // В цикле проверяем все ли данные пришли
    {
        if (!m_nNextBlockSize)
        {
            if (t_socket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (t_socket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }

        int num=10;
        QString name="десять";
        in << num << name;

        QString str=QString::number(num)+" - "+name;

        m_nNextBlockSize = 0;

        sendToClient(t_socket, num, name);

        qDebug() << "Server Response: Received \"" + str + "\"";
    }
}

// --------------------------------- Отправляем сообщение клиенту ----------------------------

void MyServer::sendToClient(QTcpSocket* t_socket, int num, const QString& str)

{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << quint16(0) << num << str;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    t_socket->write(arrBlock);
}






