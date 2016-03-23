#include "showsaving.h"
#include "ui_showsaving.h"
#include <QPainter>
#include <QMessageBox>
//#include <QLabel>
showsaving::showsaving(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::showsaving),step(0),speed(1000)
{
    ui->setupUi(this);
    ui -> horizontalSlider -> setRange(500, 1000);
    ui -> progressBar -> setValue(0);
    fil = fopen("/Users/qianzhi/Downloads/keshe/nums", "r");
    fscanf(fil, "%lf", &jmp);
    jmp = 100.00 / jmp;
    val = 0;
    //fclose(fil);
}

showsaving::~showsaving()
{
    delete ui;
}

void showsaving::showimage(int i)
{
    char tmp[64];
    sprintf(tmp,"%d",i);
    QString t =tmp;
    QString s = path1 +t+ ".jpg";   //这里是绝对路径，灰常重要
    QImage* img=new QImage;
    if(img->load(s))
        ui->label->setPixmap(QPixmap::fromImage(*img));         //important:图像显示在label上
    else
    {
        QMessageBox msgBox;
        msgBox.setText("It has been fininshed");
        msgBox.exec();
    }
}

void showsaving::showimage2(int i)
{
    char tmp[64];
    sprintf(tmp,"%d",i);
    QString t =tmp;
    QString s = path2 +t+ ".jpg";   //这里是绝对路径，灰常重要
    QImage* img=new QImage;
    if(img->load(s))
        ui->label_4->setPixmap(QPixmap::fromImage(*img));         //important:图像显示在label_4上
}

void showsaving::timerEvent(QTimerEvent *event)
{
    char tmp[64];
    sprintf(tmp,"%d",step);
    QString t =tmp;
    QString s = path1 +t+ ".jpg";    //还有这里
    QString s2 = path2 +t+ ".jpg";   //第二张图的路径
    QImage* img=new QImage;
    QImage* img2 = new QImage;
    if(img->load(s)){
        ui->label->setPixmap(QPixmap::fromImage(*img));
        img2->load(s2);
        ui->label_4->setPixmap(QPixmap::fromImage(*img2));
        val += jmp;
        ui -> progressBar -> setValue(val);
        step++;
    }
    else killTimer(id);
}

void showsaving::singlestep()
{
    killTimer(id);
    val += jmp;
    ui -> progressBar -> setValue(val);
    showimage(step);
    showimage2(step);
    step++;
}

void showsaving::premanentstep(int sp)
{
    speed = sp ;
    singlestep();
    if(id)
        killTimer(id);
    id = startTimer(speed);
}

void showsaving::stop()
{
    killTimer(id);
}

void showsaving::continuestep()
{
    singlestep();
    id = startTimer(speed);
}

void showsaving::reset()
{
    killTimer(id);
    showimage(0);
    showimage2(0);
    step = 0;
    speed = 1000;
    ui -> progressBar -> setValue(0);
    val = 0;
}

void showsaving::setstep(int i)
{
    step = i;
    showimage(step);
    showimage2(step);
}

void showsaving::on_pushButton_2_clicked()
{
    singlestep();
}



void showsaving::on_pushButton_3_clicked()
{
    speed = ui -> horizontalSlider -> value();
    continuestep();
}

void showsaving::on_pushButton_clicked()
{
    stop();
}

void showsaving::on_pushButton_4_clicked()
{
    reset();
}

void showsaving::setpath(QString p1, QString p2 )
{
    path1 = p1;
    path2 = p2;
}

//void showsaving::setlabel(QLabel *l1, QLabel *l2)
//{
//    labelname1 = l1;
//    labelname2 = l2;
//}
