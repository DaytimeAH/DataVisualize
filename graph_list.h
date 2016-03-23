#define maxn 1000
#define maxm 2000

#ifndef GRAPH_LIST
#define GRAPH_LIST

#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iostream>
#include <DG.h>
#include <shuzu.h>
class E{
public:
    int u , to , cost ;
    int next;
    E(int a  = 0, int b = 0 , int c =  0){ u = a ; to = b ; cost = c; }
};

class G{

public :
    int numnode;
    int head[maxn];
    E edge[maxm];
    int ve[maxn];
    int vl[maxn];
    bool hsh[55555];
    G() { init(); }
    ~G();
    void addedge(int from , int to , int weight);
    bool changeedge(int u , int v , int& c);
    void setnumnode(int n ){ numnode = n ;}
    void init();
    string convertstring(int& num);//Convert a number into string, modifying nothing. like: 3 to "3", etc.
    string path ;
    void toporder();
    void Criticalpath();
    bool Getanswer();
    void outputnums();
    DG DotG;
    void showciritical();
    void generatewuzhui();
    shuzu wu;
private:
    int tot;
    int flag;
    bool ring;
    int piccnt;
};



#endif // GRAPH_LIST

