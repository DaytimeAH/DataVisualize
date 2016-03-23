#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include<fstream>
#include<stdlib.h>
#include <windows.h>
using namespace std;

bool generateJPG(const char* dvpath)//Only runs on windows.
{
    string run = "dot ";
    run += dvpath;
    run += " -Tjpg -O";
    return WinExec(run.c_str(), SW_HIDE);
}

class dot_graph
{
private:
    string dot_phrase;
    string getstring(string n)//Returns the name of the node, changint the special char into its escapes.
    {
        string esc;
        unsigned int num = n.length();
        for(unsigned int i = 0; i < num; ++i)
        {
            if(n[i] == '"' || n[i] == '\\')
            {
                esc += '\\';
                esc += n[i];
            }
            else
            {
                esc += n[i];
            }
        }
        //std::cout << esc << std::endl;
        return esc;
    }
  string  conver2string(int i)
    {
        char aa[66];
        sprintf(aa, "%d", i);
        string ret(aa);
        return ret;
    }
public:
    void init()
    {
        dot_phrase="digraph g { \n nodesep=.05;\n rank=LR;\n node[shape=record,width=0.1,height=.1];\n ";
    }
    void Long(int oong,string *Name)
    {
        int i;
        string T="0";
        dot_phrase+="node0[label=\"";
        for(i=0;i<oong;i++)
        {
            dot_phrase+="<f"+conver2string(i)+">";
            if(Name[i]!=T)
            {
                dot_phrase+=getstring(Name[i]);
            }
            dot_phrase+="|";
        }
        dot_phrase+="\",height=.1];\n";
        dot_phrase+="node[width=.1];\n";
    }
    void addedge(int i,int j,int weight,int times,string *Name,int allnode)
    {

        if(times==0)
        {
            dot_phrase+="node"+conver2string(allnode)+"[label=\"{<n>"+conver2string(weight)+"|"+getstring(Name[j])+"|<p>}\"];\n";
            dot_phrase+="node"+conver2string(0)+":f"+conver2string(i)+"->node"+conver2string(allnode)+":n;\n";
        }
        else
        {
            dot_phrase+="node"+conver2string(allnode)+"[label=\"{<n>"+conver2string(weight)+"|"+getstring(Name[j])+"|<p>}\"];\n";
            dot_phrase+="node"+conver2string(allnode-1)+":p->node"+conver2string(allnode)+":n;\n";
        }
    }
    bool getdv(const char* path)//Creates the .gv file.
    {
        FILE* ofile = fopen(path, "w");
        if(ofile == NULL) return false;
        int num = dot_phrase.length();
        for(int i = 0; i < num; ++i)
        {
            fprintf(ofile, "%c", dot_phrase[i]);
        }
        fprintf(ofile, "}\n");
        fclose(ofile);
        return true;
    }
};
string Agetstring(char *n)
    {
        string ret(n);
        return ret;
    }
string  Aconverstring(int i)
    {
        char aa[66];
        sprintf(aa, "%d", i);
        string ret(aa);
        return ret;
    }

int main()
{
    int i,oong,times,from=0,after=0,weight=0,t;
    int allnode;
    ifstream infile;
    string Name[10000]={"0"};
    string aout="C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\out";
    string bout;
    char buff[1024];
    int mmun=0;
    dot_graph DV;
    DV.init();
    infile.open("C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\a.txt");
    infile.getline(buff,sizeof(buff));
    oong=atoi(buff);
    allnode=10+oong;
    DV.Long(oong+1,Name);
    bout=aout+Aconverstring(mmun);
    mmun++;
    DV.getdv(bout.c_str());
    generateJPG(bout.c_str());
    for(i=0;i<oong;i++)
    {
        infile.getline(buff,sizeof(buff));
        Name[i+1]=Agetstring(buff);
        DV.init();
        DV.Long(oong+1,Name);
       bout=aout+Aconverstring(mmun);
       mmun++;
       DV.getdv(bout.c_str());
        generateJPG(bout.c_str());
    }
    DV.init();
    DV.Long(oong+1,Name);
    times=0;
    while(!infile.eof())
    {
        infile.getline(buff,sizeof(buff));
        if(buff[0] == 'f')
        break;
        t=atoi(buff);
        if(t!=from)
        {
            times=0;
            from=t;
            infile.getline(buff,sizeof(buff));
            after=atoi(buff);
            infile.getline(buff,sizeof(buff));
            weight=atoi(buff);
            DV.addedge(from,after,weight,times,Name,allnode);
            allnode++;
            bout=aout+Aconverstring(mmun);
            mmun++;
            DV.getdv(bout.c_str());
            generateJPG(bout.c_str());
            
        }
        else
        {
            times++;
            infile.getline(buff,sizeof(buff));
            after=atoi(buff);
            infile.getline(buff,sizeof(buff));
            weight=atoi(buff);
            DV.addedge(from,after,weight,times,Name,allnode);
            allnode++;
            bout=aout+Aconverstring(mmun);
            mmun++;
            DV.getdv(bout.c_str());
            generateJPG(bout.c_str());
        }
    }
    
    FILE* fff = fopen("C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\nums", "w+");
    fprintf(fff, "%d\n", mmun);
    fclose(fff);
    return 0;
}
