#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SelectDialog)
{
    ui->setupUi(this);

    connect(ui->clientButton,   &QPushButton::clicked,  this,   &SelectDialog::select_client);
    connect(ui->serverButton,   &QPushButton::clicked,  this,   &SelectDialog::select_server);
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

// ------------------------ Нажали сервер -------------------------

void SelectDialog::select_server()
{
    emit select_signal("server");
}

// ------------------------ Нажали клиент -------------------------

void SelectDialog::select_client()
{
    emit select_signal("client");
}
