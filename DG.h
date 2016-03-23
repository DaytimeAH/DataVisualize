#ifndef DG_H
#define DG_H

#include <QMessageBox>
#include "t2gv.h"

class DG
{

public:
    //explicit DG(QWidget *parent = 0);
    DG()
    {
        NodeNum = 0;
        DGraph = new dot_graph;
        SetInit();
    }
    ~DG();
    int AddNode(string name);
    int AddEdge(string namea, string nameb, int weight);
    void SetPointHighlight(string name);
    void SetPointHighlight(int pidx);
    void Init();
    void changeedge(int fr, int to, int wh);
    void SetEdgeHighlight(string from, string to);
    void SetEdgeHighlight(int fridx, int toidx);
    void SetEdgeHighlight(int edidx);
    void BuildGraph(string out);
    int QueryPoint(string name);
    string QueryPoint(int idx);
    int QueryEdge(string from, string to);
    int QueryEdge(int fromidx, int toidx);
    int AddEdge(unsigned int idxa, unsigned int  nameb, int weight);


private:
    //Ui::Dialog *ui;
    void SetImage(const char* path);
    void SetInit();
    unsigned NodeNum;
    dot_graph* DGraph;
    map<string, int> hsmap;
    DGNode Nodes[10010];
    vector<DGEdge> Edges;
    bool HighlightNodes[10010];
    bool HighlightEdges[10010];
    map<DGEdge, int> Edge_idx;
};

#endif // DG_H
