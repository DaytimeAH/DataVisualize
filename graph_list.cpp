#include "graph_list.h"
#include "ui_graph.h"
#include <QDebug>
#include <QString>
#include <iostream>
#include <QByteArray>
void G::init()
{
    memset(head, -1 , sizeof(head));
    tot = 0 ; numnode = 0; ring = 0 ;
    memset(ve , 0 , sizeof(ve));
    memset(hsh , 0 , sizeof(hsh));

    piccnt = 0;
    path = "C:\\Users\\x86\\Desktop\\DataVisualizer\\gg\\out";
}

G:: ~G()
{
}

string G:: convertstring(int& num)
{
    char aa[66];
    sprintf(aa, "%d", num);
    string ret(aa);
    num++;
    return ret;
}

void G::addedge(int from , int to , int weight)
{
    //std:: cout << from << ' ' << to <<  ' ' << weight << std :: endl;

    if(!hsh[from]) {numnode ++ ; hsh[from] = 1 ;}
    if(!hsh[to]) {numnode ++ ; hsh[to] = 1 ;}

    //DGthis.AddEdge(t1.data(),t2.data(),t3.data());
    edge[tot].u = from ;
    edge[tot].to = to;
    edge[tot].cost = weight;
    edge[tot].next = head[from];
    head[from] = tot++;
}

void G:: generatewuzhui()
{
    FILE* f = fopen("C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\a.txt","w+");
    if(f == NULL) { qDebug("%d",111);}
    int n = numnode;
    fprintf(f , "%d\n", n);
    for(int i = 0 ; i < n;++i)
    {
        string name = DotG.QueryPoint(i);
        fprintf(f, "%s\n" , name.c_str());
    }
    for(int i = 0 ; i < n ;++i)
    {
        for(int j = head[i]; j != -1 ; j = edge[j].next)
        {
            fprintf(f, "%d\n", i+1);
            fprintf(f ,"%d\n" , edge[j].to+1);
            fprintf(f , "%d\n",edge[j].cost);
        }
    }
    fprintf(f,"f");
    fclose(f);
}

void G:: outputnums()
{
    FILE* f = fopen("C:\\Users\\x86\\Desktop\\DataVisualizer\\gg\\laodanum","w+");
    int n = piccnt;
    fprintf(f ,"%d" , n);
    fclose(f);
}


void G::toporder()
{
    std :: queue<int> Q;
    int n = numnode;
    int cnt[maxn];
    for(int i = 0 ; i <= n;++i) cnt[i] = 0 ;
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = head[i]; j != -1 ; j = edge[j].next)
        {
            //cout << i << "->" << edge[j].to << endl;
            cnt[edge[j].to] ++;

        }

    }
    for(int i = 0 ; i < n ; ++i)
    {
        if(!cnt[i])
        {
            Q.push(i);
        }
    }
    flag = 0 ;
    while(!Q.empty())
    {
        int now = Q.front();
        DotG.SetPointHighlight(now);
        wu.change(2,0,0,n);
        string t = convertstring(piccnt);
        DotG.BuildGraph(path + t);
        Q.pop();
        flag ++ ;
        std::cout << now << ' '  ;
        for(int i = head[now] ; i != -1 ; i = edge[i].next)
        {
            int to = edge[i].to;
            if(-- cnt[to] == 0)
            {
                Q.push(to);
            }
        }
    }
    std::cout << std::endl;
}

void G:: Criticalpath()
{
    int n = numnode;
    for(int i = 0 ; i < n ; ++i)
    {
      for(int j = head[i] ; j != -1 ; j = edge[j].next)
      {
         int k = edge[j].to;
         ve[k] = std :: max(ve[i] + edge[j].cost , ve[k]);
         DotG.SetPointHighlight(k);
         string t = convertstring(piccnt);
         DotG.BuildGraph(path + t);
         wu.change(1,k,ve[k],n);
      }
    }
    for(int i =  0 ; i < n ; ++i) vl[i] = ve[n-1];
    for(int i =  n - 2 ; i >= 0 ; --i)
    {
        for(int j = head[i] ; j != -1 ; j = edge[j].next)
        {
            int k = edge[j].to;
            vl[i] = std :: min(vl[i] , vl[k] - edge[j].cost);
            DotG.SetPointHighlight(k);
            string t = convertstring(piccnt);
            DotG.BuildGraph(path + t);
            wu.change(0,k,vl[k],n);
        }
    }

}
void G::showciritical()
{
    int n = numnode;
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = head[i] ; j != -1 ; j = edge[j].next)
        {
            int to = edge[j].to;
            int e = ve[i];
            int l = vl[to] - edge[j].cost;
            if( l == e)
            {
                DotG.SetPointHighlight(i);
                DotG.SetPointHighlight(to);
                //std :: cout << i << "->" << to << " is critical road" << std :: endl;
                DotG.SetEdgeHighlight(i, to);
            }
        }
    }
    string t = convertstring(piccnt);
    DotG.BuildGraph(path + t);
    wu.change(2,0,0,n);
    wu.numinit();
}

bool G:: Getanswer()
{
    int n = numnode;
    //cout << "f: " << flag << endl;
    if(flag < numnode) {  std :: cout << "has ring" << std :: endl; ring = 1;  return false ;}
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = head[i] ; j != -1 ; j = edge[j].next)
        {
            int to = edge[j].to;
            int e = ve[i];
            int l = vl[to] - edge[j].cost;
            qDebug("%d %d",e , l);
            if( l == e)
            {
                std :: cout << i << "->" << to << " is critical road" << std :: endl;
                DotG.SetEdgeHighlight(i, to);
                string t = convertstring(piccnt);
                DotG.BuildGraph(path + t);
                wu.change(2,0,0,n);
            }
        }
    }
    showciritical();
    return true;
}

bool G::changeedge(int u, int v, int& c)
{
    for(int i = head[u]; i != -1 ; i = edge[i].next)
    {
        int to = edge[i].to;
        if(to == v)
        {
            edge[i].cost = c;
            return true ;
        }

    }
    return false ;

}
