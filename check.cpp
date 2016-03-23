#include "check.h"
#include "ui_check.h"

check::check(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::check)
{
    ui->setupUi(this);
}

check::~check()
{
    delete ui;
}


