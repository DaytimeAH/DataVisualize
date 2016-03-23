#ifndef MAINGRAPHV2_H
#define MAINGRAPHV2_H

#include <QMainWindow>
#include <QLayout>
#include <QAction>
#include <QMenu>
#include <graphgraphicsview.h>
#include <adjacencylist.h>
#include <graphdrawingdialog.h>
namespace Ui {
class Maingraphv2;
}


namespace Ui {
class Maingraphv2;
}

class Maingraphv2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Maingraphv2(QWidget *parent = 0);
    ~Maingraphv2();
public slots:
    void clearScene_Triggered();
    void readFromFile_Triggered();
    void randomize_Triggered();
    void reposition_Triggered();
    void runDijkstra_Triggered();
    void specifiedGraph_Triggered();
    void runDFS_Triggered();

private slots:
    void on_Maingraphv2_toolButtonStyleChanged(const Qt::ToolButtonStyle &toolButtonStyle);

private:
    Ui::Maingraphv2 *ui;

    GraphGraphicsView* view;

    graphDrawingDialog* dialog;


    QAction* specifiedGraph;
    QAction* clearScene;
    QAction* readFromFile;
    QAction* randomize;
    QAction* reposition;
    QAction* runDijkstra;
    //QAction* runDFS;

    QMenu* Algorithms;
    QMenu* Clear;
    QMenu* Graph;

};

#endif // MAINGRAPHV2_H
