#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    ScreenSize = new MaxScreenSize();
    screen_w = ScreenSize->Screen_Width();
    screen_h = ScreenSize->Screen_Height();
    Background = new QLabel(this);
    Background->setStyleSheet("border-image: url(:/res/fone.jpg);");
    this->setCentralWidget(Background);

    init_players_name();
}

MainWindow::~MainWindow()
{
    delete Background;
    delete ScreenSize;
}

// ---------------_----- Инициализация экрана ввода имени -------------------------------

void MainWindow::init_players_name()
{
    label_name = new QLabel(this);
    label_name->setText("Как Вас величать?");
    label_name->resize(screen_w/4, screen_h/20);
    label_name->move(screen_w/2-label_name->width()/2, screen_h/3);
    label_name->setStyleSheet(QString("font-size: %1px").arg(52)+"; color: blue");
    lineedit_name = new QLineEdit(this);
    lineedit_name->resize(screen_w/4, screen_h/20);
    lineedit_name->move(label_name->x(), label_name->y()+label_name->height()+20);
    lineedit_name->setStyleSheet(QString("font-size: %1px").arg(42)+"; color: red; border-image: url(:/res/prosrach.png);");
    button_name = new QPushButton(this);
    button_name->setStyleSheet("border-image: url(:/res/ok.png);");
    button_name->resize(screen_w/30, screen_h/20);
    button_name->move(lineedit_name->x()+lineedit_name->width()/2-button_name->width()/2,
                      lineedit_name->y()+lineedit_name->height()+button_name->height()/2);

    connect(button_name,    &QPushButton::clicked,  this,   &MainWindow::input_name_player);
}

// --------------------------- Вводим имя игрока ----------------------------------------

void MainWindow::input_name_player()
{
    namePlayer = lineedit_name->text();
    if(namePlayer!="")
    {
        disconnect(button_name,    &QPushButton::clicked,  this,   &MainWindow::input_name_player);
        delete lineedit_name;
        delete label_name;
        delete button_name;
    }
}

// ------------------------- Зацикливаем пока имя не будет введено -----------------------

void MainWindow::check_name()
{
     if(namePlayer=="") check_name();
}

