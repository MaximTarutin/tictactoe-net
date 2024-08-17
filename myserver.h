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
    void server_start();                            // Прослушиваем порт
    bool chek_port(int port);                       // Проверка на свободность порта
    int i=0;
    QList <QTcpSocket*> clientura;

private:

private slots:
    void new_connection();                          // новое соединение
    void get_data();                                // получаем данные от клиента
};

#endif // MYSERVER_H
