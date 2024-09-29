
/***********************************************
 *      Структура передачи и приема данных:    *
 * номер клетки-значение клетки-активный игрок *
 * *********************************************/

#include "mainwindow.h"
#include "qapplication.h"
#include <QInputDialog>
#include <QDataStream>
#include <QScreen>
#include <QList>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    srand(time(NULL));

    background = new QLabel(this);
    background->setStyleSheet("border-image: url(:/res/fone.jpg);");           // ставим фон
    this->setCentralWidget(background);

    mediaplayer = new QMediaPlayer;
    audiooutput = new QAudioOutput;
    mediaplayer->setAudioOutput(audiooutput);
    mediaplayer->setSource(QUrl("qrc:/res-sound/1.wav"));
    audiooutput->setVolume(100);

    t_socket = new QTcpSocket(this);
    select_dialog = new SelectDialog(this);
    window_victory = new QLabel(this);
    timer_victory = new QTimer(this);

    pushButton_1 = new QPushButton(this);
    pushButton_2 = new QPushButton(this);
    pushButton_3 = new QPushButton(this);
    pushButton_4 = new QPushButton(this);
    pushButton_5 = new QPushButton(this);
    pushButton_6 = new QPushButton(this);
    pushButton_7 = new QPushButton(this);
    pushButton_8 = new QPushButton(this);
    pushButton_9 = new QPushButton(this);
    pushButton_exit = new QPushButton(this);

    QFont font;
    font.setBold(true);
    font.setPixelSize(16);

    pushButton_exit->resize(80,40);
    pushButton_exit->move(40, Screen_Height()-60);
    pushButton_exit->setText("Выход");
    pushButton_exit->setStyleSheet("background-color: red; color: blue;");
    pushButton_exit->setFont(font);

    label_score_1 = new QLabel(this);
    label_score_2 = new QLabel(this);

    movie_blue_ballon = new QMovie(":/res/blue-balloon-t.gif");
    blue_ballon = new QLabel(this);
    movie_green_ballon = new QMovie(":/res/green-balloon.gif");
    green_ballon = new QLabel(this);
    movie_sun = new QMovie(":/res/soleil-sunshine.gif");
    sun = new QLabel(this);
    movie_butterfly = new QMovie(":/res/borboletas-butterflies.gif");
    butterfly = new QLabel(this);label_info = new QLabel(this);
    movie_butterfly_1 = new QMovie(":/res/butterfly-freedom.gif");
    butterfly_1 = new QLabel(this);

    label_info->hide();
    label_score_1->hide();
    label_score_2->hide();
    blue_ballon->hide();
    butterfly->hide();
    butterfly_1->hide();
    green_ballon->hide();
    sun->hide();
    pushButton_1->hide();
    pushButton_2->hide();
    pushButton_3->hide();
    pushButton_4->hide();
    pushButton_5->hide();
    pushButton_6->hide();
    pushButton_7->hide();
    pushButton_8->hide();
    pushButton_9->hide();

    select_dialog->setWindowFlag(Qt::FramelessWindowHint);
    select_dialog->move(Screen_Width()/2-select_dialog->width()/2,
                        Screen_Height()/2-select_dialog->height()/2);
    select_dialog->setStyleSheet("border-image: url(:/res/prosrach.png);");
    select_dialog->show();

    connect(select_dialog, &SelectDialog::select_signal, this, &MainWindow::get_signal_select); // получаем сигнал из диалога
    connect(t_socket, &QTcpSocket::readyRead, this, &MainWindow::get_data);                     // получаем данные от сервера

    connect(pushButton_1, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(pushButton_2, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(pushButton_3, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(pushButton_4, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(pushButton_5, &QPushButton::clicked, this, &MainWindow::set_playing_field);     // выбираем клетку
    connect(pushButton_6, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(pushButton_7, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(pushButton_8, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(pushButton_9, &QPushButton::clicked, this, &MainWindow::set_playing_field);
    connect(timer_victory, &QTimer::timeout, this, &MainWindow::label_victory_hide);
    connect(pushButton_exit, &QPushButton::clicked, this, [](){exit(0);});
}

MainWindow::~MainWindow()
{
    delete background;
    delete label_score_2;
    delete label_score_1;
    delete t_server;
    delete window_victory;
    delete timer_victory;
    delete select_dialog;
    delete pushButton_1;
    delete pushButton_2;
    delete pushButton_3;
    delete pushButton_4;
    delete pushButton_5;
    delete pushButton_6;
    delete pushButton_7;
    delete pushButton_8;
    delete pushButton_9;
    delete label_info;
    delete movie_blue_ballon;
    delete blue_ballon;
    delete movie_green_ballon;
    delete green_ballon;
    delete sun;
    delete movie_sun;
    delete butterfly;
    delete movie_butterfly;
    delete butterfly_1;
    delete movie_butterfly_1;
    delete pushButton_exit;
    delete mediaplayer;
    delete audiooutput;
}

//------------------- Ширина экрана ------------------------------

int MainWindow::Screen_Width()
{
    QScreen *screen = QApplication::screens().at(0);
    int _width_ = screen->size().width();
    return(_width_);
}


//------------------- Высота экрана ------------------------------

int MainWindow::Screen_Height()
{
    QScreen *screen = QApplication::screens().at(0);
    int _heighrt_ = screen->size().height();
    return(_heighrt_);
}

// ------------------------- Прорисовка поля -------------------------

void MainWindow::show_field()
{
    background->setStyleSheet("border-image: url(:/res/fone.jpg);");           // ставим фон
    setStyleSheet( "QMessageBox{border-image: url(:/res/prosrach.png);}"
                  "QInputDialog {border-image: url(:/res/prosrach.png);};");
    label_score_1->setStyleSheet("border-image: url(:/res/prosrach.png); "
                                     "background-color: yellow; color: blue;");
    label_score_2->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                     "background-color: yellow; color: blue;");
    label_score_1->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label_score_2->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    QFont font;
    font.setItalic(false);
    font.setPixelSize(24);
    font.setBold(true);
    label_score_1->setFont(font);
    label_score_2->setFont(font);
    pushButton_1->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                    "background-color: pink;");
    pushButton_2->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                    "background-color: pink;");
    pushButton_3->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                    "background-color: pink;");
    pushButton_4->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                    "background-color: pink;");
    pushButton_5->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                    "background-color: pink;");
    pushButton_6->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                    "background-color: pink;");
    pushButton_7->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                    "background-color: pink;");
    pushButton_8->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                    "background-color: pink;");
    pushButton_9->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                    "background-color: pink;");
    label_info->setStyleSheet("border-image: url(:/res/prosrach.png);"
                              "color: magenta;");
    font.setItalic(true);
    label_info->setFont(font);

    pushButton_1->resize(Screen_Width()/20, Screen_Height()/10);
    pushButton_2->resize(Screen_Width()/20, Screen_Height()/10);
    pushButton_3->resize(Screen_Width()/20, Screen_Height()/10);
    pushButton_4->resize(Screen_Width()/20, Screen_Height()/10);
    pushButton_5->resize(Screen_Width()/20, Screen_Height()/10);
    pushButton_6->resize(Screen_Width()/20, Screen_Height()/10);
    pushButton_7->resize(Screen_Width()/20, Screen_Height()/10);
    pushButton_8->resize(Screen_Width()/20, Screen_Height()/10);
    pushButton_9->resize(Screen_Width()/20, Screen_Height()/10);

    int x1 = Screen_Width()/2-pushButton_1->width()-pushButton_1->width()/2;
    int y1 = Screen_Height()/2-pushButton_1->height()-pushButton_1->height()/2;
    int x2 = x1+pushButton_2->width()+10;
    int y2 = y1+pushButton_2->height()+10;
    int x3 = x2+pushButton_2->width()+10;
    int y3 = y2+pushButton_2->height()+10;

    pushButton_1->move(x1,y1);
    pushButton_2->move(x2,y1);
    pushButton_3->move(x3,y1);
    pushButton_4->move(x1,y2);
    pushButton_5->move(x2,y2);                                  // игровое поле
    pushButton_6->move(x3,y2);
    pushButton_7->move(x1,y3);
    pushButton_8->move(x2,y3);
    pushButton_9->move(x3,y3);

    label_score_1->setText(QString::number(score_player_1));
    label_score_2->setText(QString::number(score_player_2));

    int w = Screen_Width()/30;
    int h = Screen_Height()/7;

    blue_ballon->setMovie(movie_blue_ballon);
    movie_blue_ballon->start();
    blue_ballon->resize(w, h);                                // Синий шарик
    movie_blue_ballon->setScaledSize(QSize(w,h));
    blue_ballon->move(x1-w*2,y1);

    green_ballon->setMovie(movie_green_ballon);
    movie_green_ballon->start();
    green_ballon->resize(w,h);                                // Зеленый шарик
    movie_green_ballon->setScaledSize(QSize(w,h));
    green_ballon->move(x3+w*2+w/2,y1);

    int w_s = Screen_Width()/20;
    int h_s = Screen_Height()/30;
    int x_s = blue_ballon->x()-w_s/4;
    int y_s = blue_ballon->y()+blue_ballon->height()+40;
    int x1_s = green_ballon->x()-w_s/4;
    int y1_s = green_ballon->y()+green_ballon->height()+40;

    label_score_1->move(x_s, y_s);
    label_score_1->resize(w_s, h_s);
    label_score_2->move(x1_s, y1_s);
    label_score_2->resize(w_s, h_s);

    label_info->move(x1+pushButton_1->width()/2, y1-h_s-25);
    label_info->resize(x3-x1, h_s);
    label_info->setAlignment(Qt::AlignCenter);

    sun->setMovie(movie_sun);
    movie_sun->start();
    movie_sun->setScaledSize(QSize(Screen_Width()/10, Screen_Height()/5));
    sun->resize(Screen_Width()/10, Screen_Height()/5);
    sun->move(Screen_Width()/25, Screen_Height()/25);

    butterfly->setMovie(movie_butterfly);
    movie_butterfly->start();
    movie_butterfly->setScaledSize(QSize(Screen_Width()/10, Screen_Height()/5));
    butterfly->resize(Screen_Width()/10, Screen_Height()/5);
    butterfly->move(Screen_Width()-Screen_Width()/7, Screen_Height()-Screen_Height()/3);

    butterfly_1->setMovie(movie_butterfly_1);
    movie_butterfly_1->start();
    movie_butterfly_1->setScaledSize(QSize(Screen_Width()/10, Screen_Height()/10));
    butterfly_1->resize(Screen_Width()/10, Screen_Height()/10);
    butterfly_1->move(Screen_Width()/7, Screen_Height()/3);

    label_info->show();
    label_score_1->show();
    label_score_2->show();
    blue_ballon->show();
    green_ballon->show();
    sun->show();
    butterfly->show();
    butterfly_1->show();
    background->show();
    pushButton_1->show();
    pushButton_2->show();
    pushButton_3->show();
    pushButton_4->show();
    pushButton_5->show();
    pushButton_6->show();
    pushButton_7->show();
    pushButton_8->show();
    pushButton_9->show();
}

// ----------------------------------- Инициализация поля ----------------------------------

void MainWindow::init()
{
    if(VICTORY_PLAYER=="Игрок 1")
    {
        window_victory->setText("Победил игрок 1");        
    }
    if(VICTORY_PLAYER=="Игрок 2")
    {
        window_victory->setText("Победил игрок 2");
    }
    if(VICTORY_PLAYER=="Ничья")
    {
       window_victory->setText("Победила дружба");
    }
    window_victory->show();
    timer_victory->start(5000);
}

// ------------------------ Выводим сообщение о победе или поражении -----------------------

void MainWindow::label_victory_hide()
{
    window_victory->hide();
    timer_victory->stop();
    mediaplayer->setSource(QUrl("qrc:/res-sound/1.wav"));

    for(int i=0; i<10; i++)
    {
        cell[i]=10;                     // приводим массив в первоначальное состояние
    }

    label_score_1->setStyleSheet("border-image: url(:/res/prosrach.png); "
                                     "background-color: yellow;");
    label_score_2->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                     "background-color: yellow;");
    label_info->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                 "background-color: yellow;");

    pushButton_1->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                "background-color: pink;");
    pushButton_2->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                "background-color: pink;");
    pushButton_3->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                "background-color: pink;");
    pushButton_4->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                "background-color: pink;");
    pushButton_5->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                "background-color: pink;");
    pushButton_6->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                "background-color: pink;");
    pushButton_7->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                "background-color: pink;");
    pushButton_8->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                "background-color: pink;");
    pushButton_9->setStyleSheet("border-image: url(:/res/prosrach.png);"
                                "background-color: pink;");

    pushButton_1->setEnabled(true); // Очищаем поле
    pushButton_2->setEnabled(true);
    pushButton_3->setEnabled(true);
    pushButton_4->setEnabled(true);
    pushButton_5->setEnabled(true);
    pushButton_6->setEnabled(true);
    pushButton_7->setEnabled(true);
    pushButton_8->setEnabled(true);
    pushButton_9->setEnabled(true);
}

// --------------------------- Получаем сигнал из диалога выбора ---------------------------

void MainWindow::get_signal_select(QString s)
{
    if(s=="server")
    {
        start_server();
        PLAYER_NAME="PLAYER_1";
    }
    if(s=="client")
    {
        start_client();
        PLAYER_NAME="PLAYER_2";
    }
    show_field();
}

// --------------------------- Запускаем сервер -------------------------------------------

void MainWindow::start_server()
{
    delete select_dialog;
    t_server = new MyServer(this);
    t_server->server_start();
    QMessageBox::information(this, "Внимание!!!", "ip сервера: "+t_server->my_ip_address());
    t_socket->connectToHost(t_server->my_ip_address(), 21111);
}

// --------------------------- Запуск клиентской части -----------------------------------

void MainWindow::start_client()
{
    delete select_dialog;
    IPSERVER = QInputDialog::getText(this,"ip адрес сервера","");           // Вводим ip-адрес сервера
    t_socket->connectToHost(IPSERVER, 21111);                               // Отправляем запрос на подключение к серверу
}

// ------------------------- Получение данных от сервера ---------------------------------

void MainWindow::get_data()
{
    QDataStream in(t_socket);
    in.setVersion(QDataStream::Qt_6_5);
    int num;
    QString str;
    QString ox;             // Времянка
    in >> num >> str;
    if(num==200)
    {
        ACTIVE_PLAYER = str;                    // Новая игра
        init();
        if(ACTIVE_PLAYER==PLAYER_NAME)
        {
            label_info->setText("ВАШ ХОД !!!");
        } else
        {
            label_info->setText("Ход противника");
        }
        qDebug() << "Новая игра, ходит: " << str;
        return;
    }

    ACTIVE_PLAYER = str;

    if(ACTIVE_PLAYER==PLAYER_NAME)
    {
        label_info->setText("ВАШ ХОД !!!");
    } else
    {
        label_info->setText("Ход противника");
    }

    if(ACTIVE_PLAYER=="PLAYER_1")
    {
        ox="border-image: url(:/res/kr.png)";
        cell[num]=1;
    } else
    {
        cell[num]=2;
        ox="border-image: url(:/res/nol.png)";
    }

    switch(num)
    {
        case 1: pushButton_1->setDisabled(true);
                pushButton_1->setStyleSheet(ox);
                break;
        case 2: pushButton_2->setDisabled(true);
                pushButton_2->setStyleSheet(ox);
                break;
        case 3: pushButton_3->setDisabled(true);
                pushButton_3->setStyleSheet(ox);
                break;
        case 4: pushButton_4->setDisabled(true);
                pushButton_4->setStyleSheet(ox);
                break;
        case 5: pushButton_5->setDisabled(true);
                pushButton_5->setStyleSheet(ox);
                break;
        case 6: pushButton_6->setDisabled(true);
                pushButton_6->setStyleSheet(ox);
                break;
        case 7: pushButton_7->setDisabled(true);
                pushButton_7->setStyleSheet(ox);
                break;
        case 8: pushButton_8->setDisabled(true);
                pushButton_8->setStyleSheet(ox);
                break;
        case 9: pushButton_9->setDisabled(true);
                pushButton_9->setStyleSheet(ox);
                break;
    }
    mediaplayer->play();
    check_to_victory();
}

// ------------------------ Отправка данных на сервер -----------------------------------

void MainWindow::send_data(int num)
{
    QString str;
    QDataStream out(t_socket);
    out.setVersion(QDataStream::Qt_6_5);
    if(ACTIVE_PLAYER!=PLAYER_NAME)
    {
        return;
    } else
    {
        if(PLAYER_NAME=="PLAYER_1") str="PLAYER_2"; else str="PLAYER_1";
        out << num << str;
    }
}

// ------------------------- Установитть состояние клетки на поле ------------------------

void MainWindow::set_playing_field()
{
    int num1=0;
    if(QObject::sender()==pushButton_1)
    {
        num1=1;
    }
    if(QObject::sender()==pushButton_2)
    {
        num1=2;
    }
    if(QObject::sender()==pushButton_3)
    {
        num1=3;
    }
    if(QObject::sender()==pushButton_4)
    {
        num1=4;
    }
    if(QObject::sender()==pushButton_5)
    {
        num1=5;
    }
    if(QObject::sender()==pushButton_6)
    {
        num1=6;
    }
    if(QObject::sender()==pushButton_7)
    {
        num1=7;
    }
    if(QObject::sender()==pushButton_8)
    {
        num1=8;
    }
    if(QObject::sender()==pushButton_9)
    {
        num1=9;
    }
    send_data(num1);
}

// --------------------------------- Проверка на победу --------------------------------

void MainWindow::check_to_victory()
{
    int col1 = cell[1]+cell[2]+cell[3];
    int col2 = cell[4]+cell[5]+cell[6];
    int col3 = cell[7]+cell[8]+cell[9];
    int row1 = cell[1]+cell[4]+cell[7];         // Возможные комбинации выигрыша
    int row2 = cell[2]+cell[5]+cell[8];
    int row3 = cell[3]+cell[6]+cell[9];
    int diag1 = cell[1]+cell[5]+cell[9];
    int diag2 = cell[3]+cell[5]+cell[7];

    if((col1==3)or(col2==3)or(col3==3)or
       (row1==3)or(row2==3)or(row3==3)or
        (diag1==3)or(diag2==3))
    {
        victory(2);
        return;
    }

    if((col1==6)or(col2==6)or(col3==6)or
       (row1==6)or(row2==6)or(row3==6)or
        (diag1==6)or(diag2==6))
    {
        victory(1);
        return;
    }

    for(int i=1; i<=9; i++)                     // Проверка на ничью
    {
        if(cell[i]==10)
        {
            return;
        }
    }
    victory(3);
}

// --------------------------------------- Победа ------------------------------------------

void MainWindow::victory(int i)
{
    if(i==1)
    {
        score_player_1++;
        VICTORY_PLAYER="Игрок 1";

        if(ACTIVE_PLAYER==PLAYER_NAME)
        {
            mediaplayer->setSource(QUrl("qrc:/res-sound/4.wav"));
            mediaplayer->play();
        } else
        {
            mediaplayer->setSource(QUrl("qrc:/res-sound/2.wav"));
            mediaplayer->play();
        }
    }
    if(i==2)
    {
        score_player_2++;
        VICTORY_PLAYER="Игрок 2";
        if(ACTIVE_PLAYER==PLAYER_NAME)
        {
            mediaplayer->setSource(QUrl("qrc:/res-sound/4.wav"));
            mediaplayer->play();
        } else
        {
            mediaplayer->setSource(QUrl("qrc:/res-sound/2.wav"));
            mediaplayer->play();
        }
    }
    if(i==3)
    {
        mediaplayer->setSource(QUrl("qrc:/res-sound/3.wav"));
        mediaplayer->play();
        VICTORY_PLAYER="Ничья";
    }

    pushButton_1->setEnabled(false);
    pushButton_2->setEnabled(false);
    pushButton_3->setEnabled(false);
    pushButton_4->setEnabled(false);
    pushButton_5->setEnabled(false);
    pushButton_6->setEnabled(false);
    pushButton_7->setEnabled(false);
    pushButton_8->setEnabled(false);
    pushButton_9->setEnabled(false);

    label_score_1->setText(QString::number(score_player_1));
    label_score_2->setText(QString::number(score_player_2));

    send_data(200);
}
