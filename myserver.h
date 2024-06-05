#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);
    ~MyServer();

    QString         my_ip_address();
    void server_start();

private:
    quint16 m_nNextBlockSize;
    void sendToClient(QTcpSocket* t_socket, int num, const QString& str);     // передаем данные клиенту

private slots:
    void new_connection();                                          // новое соединение
    void get_data();                                                // получаем данные от клиента
};

#endif // MYSERVER_H
