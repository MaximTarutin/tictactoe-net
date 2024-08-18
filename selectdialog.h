#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QObject>
#include <QWidget>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SelectDialog(QWidget *parent = nullptr);
    ~SelectDialog();

private:
    Ui::SelectDialog *ui;

signals:
    void select_signal(QString s);      // s = "server" or "client"

private slots:
    void select_server();               // нажали сервер
    void select_client();               // нажали клиент
};

#endif // SELECTDIALOG_H
