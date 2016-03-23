#ifndef Graph_H
#define Graph_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QListView>
#include <cstring>
#include "visualizer.h"
#include "graph_list.h"
#include <qvalidator.h>
#include "showqianzhi.h"
#include "shuzu.h"
//#include <QPointF>

namespace Ui {
class Graphv;
}

class Graphv : public QWidget
{
    Q_OBJECT

public:
    explicit Graphv(QWidget *parent = 0);
    ~Graphv();
    int cntnode ;
    int idd ;
    void clearLine() ;

    void cleanupElem(Ui::EllipseElement *node);

    int removeEdge(int idx, QString val);
    void Listshow();
    void generateword(QString t1 , QString t2 , QString t3);
    void showlist2();
    void timerEvent(QTimerEvent *t);

private slots:
    void on_addedgeButton_clicked();

    void on_EnterButton_clicked();

    void on_clearButton_clicked();

    void on_changButton_clicked();
    void gogo();
    void on_testButton_clicked();

private:
    int id1 ,id2 , id3;
    Ui::Graphv *ui;
    QGraphicsScene *scene;
    QValidator *v;
    G Graph;
    shuzu wu;

};

#endif
