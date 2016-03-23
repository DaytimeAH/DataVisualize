#include "graphdrawingdialog.h"
#include "ui_graphdrawingdialog.h"

graphDrawingDialog::graphDrawingDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphDrawingDialog)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);


    QObject::connect(ui->cancelButton, SIGNAL(clicked()),
                     this, SLOT(close()));
    QObject::connect(ui->okButton, SIGNAL(clicked()),
                     this, SLOT(okButtonPressed()));
}

graphDrawingDialog::~graphDrawingDialog()
{
    delete ui;
}

void graphDrawingDialog::okButtonPressed()
{
    int vertices = ui->vertexSpinbox->value();
    int edges = ui->edgeSpinbox->value();
    if(vertices*vertices > edges)
    {
        drawThis(vertices,edges);
    }
    else
    {
        drawThis(vertices,vertices);
    }
    this->hide();
}
