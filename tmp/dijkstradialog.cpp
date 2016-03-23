#include "dijkstradialog.h"
#include "ui_dijkstradialog.h"

dijkstraDialog::dijkstraDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dijkstraDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->okButton, SIGNAL(pressed()),
                     this, SLOT(okButton_Pressed()));
    QObject::connect(ui->cancelButton, SIGNAL(pressed()),
                     this, SLOT(close()));

    this->setWindowTitle("Source, destination chooser");
}

dijkstraDialog::~dijkstraDialog()
{
    delete ui;
}

void dijkstraDialog::setSize(int size)
{
    ui->fromBox->clear();
    ui->toBox->clear();
    for (int i = 1; i <= size; ++i) {
        ui->fromBox->addItem(QString::number(i));
        ui->toBox->addItem(QString::number(i));
    }
}

void dijkstraDialog::okButton_Pressed()
{
    int from = ui->fromBox->currentText().toInt() - 1;
    int to = ui->toBox->currentText().toInt() - 1;
    runDijkstraFromTo(from, to);
    this->close();
}
