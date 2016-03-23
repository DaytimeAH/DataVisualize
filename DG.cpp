#include "DG.h"

void deb(const char aa[256])
{
    QMessageBox::critical(0 ,
    "critical message" , aa,
    QMessageBox::Ok | QMessageBox::Default ,
    QMessageBox::Cancel | QMessageBox::Escape , 	0 );
}


DG::~DG()
{

}

void DG::SetImage(const char* path)
{
    //WRITE

}

int DG::QueryPoint(string name)
{
    map<string, int>::iterator m1 = hsmap.find(name);
    if(m1 == hsmap.end()) return -1;
    return hsmap[name];
}

string DG::QueryPoint(int idx)
{
    string F(Nodes[idx].name);
    return F;
}

int DG::QueryEdge(string from, string to)
{
    DGNode* a = &Nodes[hsmap[from]];
    DGNode* b = &Nodes[hsmap[to]];
    DGEdge ed(a, b, 0);
    return Edge_idx[ed];
}

int DG::QueryEdge(int fridx, int toidx)
{
    DGNode* a = &Nodes[fridx];
    DGNode* b = &Nodes[toidx];
    DGEdge ed(a, b, 0);
    return Edge_idx[ed];
}

int DG::AddNode(string nm)
{
    //std::cout << nm << std::endl;
    if(QueryPoint(nm) != -1) return QueryPoint(nm);
    hsmap[nm] = NodeNum;
    Nodes[NodeNum].name = nm;
    Nodes[NodeNum].index = NodeNum;
    ++NodeNum;
    return hsmap[nm];
}

int DG::AddEdge(string namea, string nameb, int weight)//Shouldn't be used after the struct of the graph is confirmed.
{
    DGNode* from = &Nodes[hsmap[namea]];
    DGNode* to = &Nodes[hsmap[nameb]];
    DGEdge ed(from, to, weight);
    Edge_idx[ed] = Edges.size();
    Edges.push_back(ed);
    return Edge_idx[ed];
}

int DG::AddEdge(unsigned int idxa, unsigned int  idxb, int weight)//Shouldn't be used after the struct of the graph is confirmed.
{
    DGNode* from = &Nodes[idxa];
    DGNode* to = &Nodes[idxb];
    DGEdge ed(from, to, weight);
    Edge_idx[ed] = Edges.size();
    Edges.push_back(ed);
    return Edge_idx[ed];
}

void DG::SetInit()//Rember to use it after having built a pic.
{
    for(int i = 0; i < 10010; ++i) HighlightEdges[i] = false;
    for(int i = 0; i < 10010; ++i) HighlightNodes[i] = false;
}

void DG::SetPointHighlight(string name)
{
    HighlightNodes[QueryPoint(name)] = true;
}

void DG::SetPointHighlight(int pidx)
{
    HighlightNodes[pidx] = true;
}

void DG::SetEdgeHighlight(string from, string to)
{
    int edid = QueryEdge(from, to);
    HighlightEdges[edid] = true;
}

void DG::SetEdgeHighlight(int fridx, int toidx)
{
    int edid = QueryEdge(fridx, toidx);
    HighlightEdges[edid] = true;
}

void DG::SetEdgeHighlight(int edidx)
{
    HighlightEdges[edidx] = true;
}

void DG::Init()
{
    NodeNum = 0;
    hsmap.clear();
    Edges.clear();
    SetInit();
    Edge_idx.clear();
}

void DG::BuildGraph(string out)
{
    DGraph -> init();
    for(unsigned int i = 0; i < NodeNum; ++i)
    {
        if(HighlightNodes[i]) DGraph -> sethighlight(Nodes[i]);
    }
    for(unsigned int i = 0; i < Edges.size(); ++i)
    {
        DGraph -> addedge(*Edges[i].from, *Edges[i].to, Edges[i].weight, HighlightEdges[i]);
    }
    DGraph -> getdv(out.c_str());
    DGraph -> generateJPG(out.c_str());
    out += ".jpg";
    SetImage(out.c_str());
    delete DGraph;
    DGraph = new dot_graph;
    SetInit();
}

void DG::changeedge(int fr, int to, int wh)
{
    int chg = QueryEdge(fr, to);
    Edges[chg].weight = wh;
}

/*
void DG::on_pushButton_clicked()
{
    char out[] = "out.gv";
    BuildGraph(out);
}
*/
