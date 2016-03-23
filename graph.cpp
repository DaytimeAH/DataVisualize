#include "graph.h"
#include "ui_graph.h"

#include <QDebug>
#include <windows.h>
#include <QMessageBox>
#include "DG.h"
#include "check.h"
#include "ui_check.h"
Graphv::Graphv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graphv)
{
    ui->setupUi(this);
    QPixmap bkgnd(":files/images/bckgnd.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //QRectF scene_coords;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    cntnode =  0;

}

Graphv::~Graphv()
{
    delete scene;
    delete ui;
}


void Graphv :: clearLine()
{
    ui -> lineEdit_F ->clear();
    ui -> lineEdit_T -> clear();
    ui -> lineEdit_W -> clear();
    //ui -> listshow -> clear();
}

void Graphv::Listshow()
{
    ui->listshow ->show();
}

void Graphv::generateword(QString t1 , QString t2 , QString t3)
{
    QString ss = "***********************";
    ui->listshow ->addItem(ss);
    ui->listshow ->addItem(tr("now adding the edge : ") + QString("%1 -> %2  weight: %3").arg(t1,t2,t3));
}

void Graphv::on_addedgeButton_clicked()
{
    QString from = ui -> lineEdit_F -> text();
    string tmpu = from.toStdString();
    QString to = ui -> lineEdit_T -> text();
    string tmpv = to.toStdString();
    QString cost = ui -> lineEdit_W -> text();

    if(from == "" || to == "" || cost == "")
    {
        QMessageBox::warning(this, tr("Waring"),
                              tr("input error!"),
                              QMessageBox::No);
        return;
    }
    qDebug("!!!!!!!!!!!");
    int u, v;
    if(Graph.DotG.QueryPoint(tmpu) == -1)
    {
        u =  Graph.DotG.AddNode(tmpu);
    }
    else
    {
        u = Graph.DotG.QueryPoint(tmpu);
    }

    if(Graph.DotG.QueryPoint(tmpv) == -1)
    {
        v =  Graph.DotG.AddNode(tmpv);
    }
    else
    {
        v = Graph.DotG.QueryPoint(tmpv);
    }
    qDebug("%d -> %d",u , v);

    int c = atoi(cost. toLatin1());
    Graph.DotG.AddEdge(u, v, c);
    Graph.addedge(u, v ,c);
    clearLine();
    generateword(from , to , cost);
    Listshow();
}

void Graphv:: gogo()
{

    ui -> listshow ->clear();
    //Graph.setnumnode(cntnode);
    qDebug("%d",cntnode);

    Graph.toporder();
    Graph.Criticalpath();
    if(Graph.Getanswer()) {qDebug("yes!"); }
    else
    {
        QMessageBox::warning(this, tr("Waring"),
                              tr("Graph has ring!"),
                              QMessageBox::Yes);
    }
    Graph.outputnums();
    showqianzhi* showaction = new showqianzhi;
    showaction->show();
}


void Graphv::showlist2()
{
    QString ss = "***********************";
    ui->listshow ->addItem(ss);
    ui->listshow ->addItem(tr("now generate the graph : please wait >>>")  );
    id1 = startTimer(1000);
    id2 = startTimer(2000);
    id3 = startTimer(3000);
}

void Graphv::timerEvent(QTimerEvent *t)
{

    if( t->timerId() == id1 )
    {
        QString run = "C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\WZW.exe";
        QProcess proc;
        proc.setWorkingDirectory("C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\");
        proc.execute("cmd", QStringList() << "/c" << run);
        ui->listshow ->addItem(tr("create the adjacentlist suceessful!"));
        Listshow();
        killTimer(id1);
    }
    if(t->timerId() == id2)
    {
        ui->listshow ->addItem(tr("creat the Graph suceessful!"));
        Listshow();
        killTimer(id2);

    }
    if(t->timerId() == id3)
    {
        ui->listshow ->addItem(tr("Algorithm working suceessful!"));
        Listshow();
        ui->listshow ->addItem(tr("Let's show it !!"));
        Listshow();
        killTimer(id3);
        gogo();
    }

}


void Graphv::on_EnterButton_clicked()
{
    check dlg ;
    if(dlg.exec() == QDialog::Accepted)
    {

        QMessageBox::warning(this, tr("Waring"),
                              tr("Graph accepted!"),
                              QMessageBox::Yes);
        Graph.generatewuzhui();
        //showaction.setpath("C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\out",""); //设置路径，形式为：/Users/qianzhi/Downloads/keshe/out，可缺省；
        showlist2();

    }
    else
    {
        QMessageBox::warning(this, tr("Waring"),
                              tr("Graph rejusted!"),
                              QMessageBox::Yes);

    }

}

void Graphv::on_clearButton_clicked()
{
    ui->listshow ->clear();
    Graph.init();
    Graph.DotG.Init();
    QProcess::execute("cmd", QStringList() << "/c" << "C:\\Users\\x86\\Desktop\\DataVisualizer\\delg1.bat");
    QProcess::execute("cmd", QStringList() << "/c" << "C:\\Users\\x86\\Desktop\\DataVisualizer\\delgg.bat");
    QProcess::execute("cmd", QStringList() << "/c" << "C:\\Users\\x86\\Desktop\\DataVisualizer\\delpics.bat");
}

void Graphv::on_changButton_clicked()
{
    QString tmpu = ui->lineEdit_F ->text();
    string u = tmpu.toStdString();
    QString tmpv = ui->lineEdit_T->text();
    string v = tmpv.toStdString();
    QString cost = ui ->lineEdit_W ->text();
    int uu = Graph.DotG.QueryPoint(u);
    int vv = Graph.DotG.QueryPoint(v);
    int c = atoi(cost. toLatin1());
    if(Graph.changeedge(uu, vv ,c))
    {
        Graph.DotG.changeedge(uu, vv, c);
        QMessageBox::warning(this, tr("Waring"),
                              tr("change accepted!"),
                              QMessageBox::Yes);
        clearLine();
        Listshow();

    }
    else
    {
        QMessageBox::warning(this, tr("Waring"),
                              tr("edge isn's exist!"),
                              QMessageBox::Yes);

    }
}

void Graphv::on_testButton_clicked()
{
    ui ->listshow ->addItem(tr("now adding nodes are"));
    ui ->listshow ->addItem(tr("a1 , a2 , a3 , a3 , a4 , a5 , a6 ,a7"));
    int a1 , a2, a3 , a4 ,a5 ,a6, a7;
    a1 = Graph.DotG.AddNode("a1");
    a2 = Graph.DotG.AddNode("a2");
    Graph.DotG.AddEdge(a1 , a2 , 1);
    Graph.addedge(a1, a2 , 1);
    ui ->listshow ->addItem(tr("now addedge : a1 -> a2 cost: 1"));

    a1 = Graph.DotG.AddNode("a1");
    a3 = Graph.DotG.AddNode("a3");
    Graph.DotG.AddEdge(a1 , a3 , 2);
    Graph.addedge(a1, a3, 2);
    ui ->listshow ->addItem(tr("now addedge : a1 -> a3 cost: 2"));

    a2 = Graph.DotG.AddNode("a2");
    a4 = Graph.DotG.AddNode("a4");
    Graph.DotG.AddEdge(a2 , a4 , 3);
    Graph.addedge(a2, a4, 3);
    ui ->listshow ->addItem(tr("now addedge : a2 -> a4 cost: 3"));

    a3 = Graph.DotG.AddNode("a3");
    a4 = Graph.DotG.AddNode("a4");
    Graph.DotG.AddEdge(a3 , a4 , 4);
    Graph.addedge(a3 , a4 , 4);
    ui ->listshow ->addItem(tr("now addedge : a3 -> a4 cost: 4"));

    a3 = Graph.DotG.AddNode("a3");
    a5 = Graph.DotG.AddNode("a5");
    Graph.DotG.AddEdge(a3 , a5 , 5);
    Graph.addedge(a3, a5, 5);
    ui ->listshow ->addItem(tr("now addedge : a3 -> a5 cost: 5"));

    a4 = Graph.DotG.AddNode("a4");
    a6 = Graph.DotG.AddNode("a6");
    Graph.DotG.AddEdge(a4 , a6 , 6);
    Graph.addedge(a4 , a6, 6);
    ui ->listshow ->addItem(tr("now addedge : a4 -> a6 cost: 6"));

    a5 = Graph.DotG.AddNode("a5");
    a7 = Graph.DotG.AddNode("a7");
    Graph.DotG.AddEdge(a5 , a7 , 7);
    Graph.addedge(a5 ,a7 , 7);
    ui ->listshow ->addItem(tr("now addedge : a5 -> a7 cost: 7"));

    a6 = Graph.DotG.AddNode("a6");
    a7 = Graph.DotG.AddNode("a7");
    Graph.DotG.AddEdge(a6 , a7 , 8);
    Graph.addedge(a6 , a7 , 8);
    ui ->listshow ->addItem(tr("now addedge : a6 -> a7 cost: 8"));
}
