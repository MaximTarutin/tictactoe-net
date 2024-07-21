#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "maxscreensize.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    

private:
    MaxScreenSize   *ScreenSize = nullptr;              // объект размер экрана
    QLabel          *Background = nullptr;              // игровой фон, центральный виджет
    QLabel          *label_name = nullptr;              // лейбл при вводе имени игрока
    QLineEdit       *lineedit_name = nullptr;           // ввод имени игрока
    QPushButton     *button_name = nullptr;             // кнопка подтверждения ввода имени

    int screen_w = 0;                                   // ширина экрана
    int screen_h = 0;                                   // высота экрана
    QString namePlayer = "";                            // имя игрока

    void init_players_name();                           // инициализация экрана ввода имени
    void check_name();                                  // проверяем введено ли имя игрока

private slots:
    void input_name_player();                           // вводим свое имя
};
#endif // MAINWINDOW_H
