#include "maingraphv2.h"
#include "ui_maingraphv2.h"


Maingraphv2::Maingraphv2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Maingraphv2)
{
    ui->setupUi(this);
    this->resize(1000,550);
    view = new GraphGraphicsView(this);
    view->show();
    view->setGeometry(view->pos().x(), view->pos().y()+20,view->size().width(), view->size().height() );
    dialog = new graphDrawingDialog();

    Graph = menuBar()->addMenu("Graph");
    /*
    Clear = menuBar()->addMenu("Clear");
    Algorithms = menuBar()->addMenu("Run Algorithms...");
    */
    Clear = ui->menuBar->addMenu("Clear");
    Algorithms = ui->menuBar->addMenu("Run Algorithms...");

    clearScene = new QAction("Clear scene", this);
    readFromFile = new QAction("Read graph from file", this);
    randomize = new QAction("Randomize graph", this);
    reposition = new QAction("Reposition graph", this);
    runDijkstra = new QAction("Run algorithm", this);
    //runDFS = new QAction("Run depth first search", this);
    specifiedGraph = new QAction("Draw specified graph...", this);

    Graph->addAction(readFromFile);
    Graph->addAction(randomize);
    Graph->addAction(reposition);
    Graph->addAction(specifiedGraph);

    Clear->addAction(clearScene);

    Algorithms->addAction(runDijkstra);
    //Algorithms->addAction(runDFS);

    menuBar()->show();
    //qDebug() << menuBar()->isVisible();

    QObject::connect(clearScene, SIGNAL(triggered()),
                     view, SLOT(clear()));
    QObject::connect(randomize, SIGNAL(triggered()),
                     view, SLOT(randomGraph()));
    QObject::connect(reposition, SIGNAL(triggered()),
                     view, SLOT(reposition()));
    //QObject::connect(runDFS, SIGNAL(triggered()),
               //      view, SLOT(depthFirstSearch()));
    QObject::connect(specifiedGraph, SIGNAL(triggered()),
                     this, SLOT(specifiedGraph_Triggered()));
    QObject::connect(dialog, SIGNAL(drawThis(int,int)),
                     view, SLOT(drawSpecifiedGraph(int,int)));
    QObject::connect(runDijkstra, SIGNAL(triggered()),
                     view, SLOT(preDijkstra()));
    QObject::connect(readFromFile, SIGNAL(triggered()),
                     view, SLOT(readFromFile()));


/*
    ui->menuBar->addMenu(Graph);
    ui->menuBar->addMenu(Algorithms);
    ui->menuBar->addMenu(Clear);
*/
}

Maingraphv2::~Maingraphv2()
{
    delete ui;
}

void Maingraphv2::clearScene_Triggered()
{
    view->clear();
}

void Maingraphv2::readFromFile_Triggered()
{
}

void Maingraphv2::randomize_Triggered()
{
    view->randomGraph();
}

void Maingraphv2::reposition_Triggered()
{
    view->reposition();
}

void Maingraphv2::runDijkstra_Triggered()
{
}

void Maingraphv2::specifiedGraph_Triggered()
{
    dialog->show();
}

void Maingraphv2::runDFS_Triggered()
{

}

void Maingraphv2::on_Maingraphv2_toolButtonStyleChanged(const Qt::ToolButtonStyle &toolButtonStyle)
{

}
