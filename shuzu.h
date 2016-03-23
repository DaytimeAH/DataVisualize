#ifndef SHUZU
#define SHUZU
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <QProcess>
using namespace std;

class shuzu
{
private:
    string dot_phrase;
    string getstring(char *n)
    {
        string ret(n);
        return ret;
    }
    string  conver2string(int i)
    {
        char aa[66];
        sprintf(aa, "%d", i);
        string ret(aa);
        return ret;
    }
    string aout;
    string bout;
    int mmun;
    string Longgist[100];
    string Shortist[100];
public:
    void generateJPG(const char* dvpath)//Only runs on windows.
    {
        QString run = "dot ";
        run += dvpath;
        run += " -Tjpg -O";
        QProcess::execute(run);
    }
    shuzu(){ numinit(); aout="C:\\Users\\x86\\Desktop\\DataVisualizer\\g1\\out";}
    void change(int m,int place,int num,int oong)
    {
        init();
        if(m==1)
        {
            Longgist[place]=conver2string(num);
        }
        else if(m==0)
        {
            Shortist[place]=conver2string(num);
        }
        Long(oong);
        bout=aout+conver2string(mmun);
        mmun++;
        getdv(bout.c_str());
        generateJPG(bout.c_str());
    }
    void numinit()
    {
        for(int i = 0 ; i < 100 ; ++i)
            Longgist[i] = "0",
            Shortist[i] = "0";
        mmun=0;
    }
    void init()
    {
        dot_phrase="digraph g { \n nodesep=.05;\n rank=LR;\n node[shape=record,width=1.0,height=1.0];\n ";
    }
    void Long(int oong)
    {
        int i;
        string T="0";
        dot_phrase+="node0[label=\"";
        for(i=0; i<oong; i++)
        {
            dot_phrase+="<f"+conver2string(i)+">";
            if(Longgist[i]==T)
            {

            }
            else
            {
                dot_phrase+=Longgist[i];
            }
            dot_phrase+="|";
        }
        dot_phrase+="\",height=.5];\n";
        dot_phrase+="node1[label=\"";
        for(i=0; i<oong; i++)
        {
            dot_phrase+="<g"+conver2string(i)+">";
            if(Shortist[i]==T)
            {

            }
            else
            {
                dot_phrase+=Shortist[i];
            }
            dot_phrase+="|";
        }
        dot_phrase+="\",height=.5];\n";

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





#endif // SHUZU

