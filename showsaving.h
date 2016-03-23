#ifndef SHOWSAVING_H
#define SHOWSAVING_H
#include <QSlider>
#include <QMainWindow>
#include <vector>
#include <QString>
#include <stdio.h>
#include <QLabel>
namespace Ui
{
    class showsaving;
}

class showsaving : public QMainWindow
{
    Q_OBJECT

public:
    explicit showsaving(QWidget *parent = 0);
    ~showsaving();

private:
    Ui::showsaving *ui;
/***********************************/
public:
    void showimage(int i);            //显示第i张图片（i均从0开始）
    void showimage2(int i);            //出第二张图的函数
    void singlestep();                //单步运行，从当前位置开始,可做下一步用
    void premanentstep(int sp);       //持续运行，从当前位置开始。sp 为速度，ms
    void stop();                      //停止持续运行
    void continuestep();              //继续持续运行
    void reset();                     //复位
    void setstep(int i);              //跳转到第i张
    void setpath(QString p1 = "/", QString p2 = "/");                   //设置路径，形式为：/Users/qianzhi/Downloads/keshe/out，可缺省；
    //void setlabel(QLabel* l1, QLabel * l2);     //设置放图片的label，失败，目前两张图片的label名分别为label和label_4,如需变更请变更源代码（或者你来把这个函数实现lol）
private:
    int step;                           //第i步
    int id;                             //QTimer的ID
    int speed;                          //持续运行速度
    double jmp;
    FILE* fil;
    double val;
    //QLabel * labelname1,* labelname2;                 //两个label
    QString path1 , path2;                      //图片路径，形式为：/Users/qianzhi/Downloads/keshe/out

protected:
    void timerEvent(QTimerEvent *event);  //timer的触发
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
};

#endif // SHOWSAVING_H
