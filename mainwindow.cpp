#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    ScreenSize = new MaxScreenSize();
    screen_w = ScreenSize->Screen_Width();
    screen_h = ScreenSize->Screen_Height();
    Background = new QLabel(this);
    Background->setStyleSheet("border-image: url(:/res/fone.jpg);");
    this->setCentralWidget(Background);
    label_name = new QLabel(this);
    label_name->setText("Как Вас величать?");
    label_name->move(300,50);
    lineedit_name = new QLineEdit(this);
    lineedit_name->move(300,100);
    button_name = new QPushButton(this);
    button_name->setText("Ok");
    button_name->move(300,150);

    connect(button_name,    &QPushButton::clicked,  this,   &MainWindow::input_name_player);
}

MainWindow::~MainWindow()
{
    delete Background;
    delete ScreenSize;
}

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

void MainWindow::check_name()
{
     if(namePlayer=="") check_name();
}

