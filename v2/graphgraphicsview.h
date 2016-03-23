#ifndef GRAPHGRAPHICSVIEW_H
#define GRAPHGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <QTime>
#include <qmath.h>
#include <math.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include "nodegraphicsitem.h"
#include "adjacencylist.h"
#include "dijkstradialog.h"
#include "filehandler.h"
#include "priorityqueue.h"

class GraphGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphGraphicsView(QWidget *parent = 0);
    
signals:
    
public slots:
    void drawSpecifiedGraph(QList<QList<int> > adjM);
    void drawSpecifiedGraph(int vertices, int edges);
    void drawShortestPath(int from, int to);
    void depthFirstSearch();
    void randomGraph();
    void reposition();
    void clear();
    void preDijkstra();
    void runDijkstra(int from, int to);
    void runPrim();
    void drawWeights();
    void readFromFile();

private:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void drawPath(NodeGraphicsItem *from, NodeGraphicsItem *to);
    void drawAllEdges();
    void clearNodes(bool Permanent = true);
    void clearArrows(bool Permanent = true);
    void drawCurrent();
    void DFS(int curr, int& depthNo, int &endNo, QList<int> &prev, bool &hasCircle);
    void Dijkstra(int s, int to);
    void CondMinSearch(QList<int> d, QList<bool> found, int &u, bool& l);
    void clearWeights();

    bool isBelow(NodeGraphicsItem *item, NodeGraphicsItem *toCheck);
    bool itemLevelTooClose(NodeGraphicsItem *first, NodeGraphicsItem *second);



    int source;
    int destination;
    dijkstraDialog* dDialog;
    QGraphicsScene scene;
    QList<NodeGraphicsItem*>   nodes;
    QList<QGraphicsLineItem*>  lines;
    QList<QGraphicsLineItem*> arrows;
    QList<AdjacencyList> adj;
    QList<QList<int> > adjMatrix;
    QList<QGraphicsTextItem*> weights;
    QList<int> prevs;
    FileHandler handler;
    PriorityQueue minQ;
};

#endif // GRAPHGRAPHICSVIEW_H
