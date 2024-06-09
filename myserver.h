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

    QString my_ip_address();                        // Получаем свой ip-адрес
    void    server_start();                         // Прослушиваем порт 21111

private slots:
    void new_connection();                          // новое соединение
    void get_data();                                // получаем данные от клиента
};

#endif // MYSERVER_H
