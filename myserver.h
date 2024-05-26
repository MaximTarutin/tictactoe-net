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

    void server_start();

private slots:
    void new_connection();
    void end_connection();
    void get_data();

public:
    QString         my_ip_address();
    QTcpSocket      *t_socket;
};

#endif // MYSERVER_H
