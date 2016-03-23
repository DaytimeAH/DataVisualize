#include "showqianzhi.h"
#include "ui_showqianzhi.h"
#include "iostream"
showqianzhi::showqianzhi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showqianzhi)
{
    ui->setupUi(this);
    ui -> horizontalSlider -> setRange(200, 600);
    ui -> progressBar -> setValue(0);
    step = 0;
    fil1 = fopen("C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\nums", "r");
    fil2 = fopen("C:\\Users\\x86\\Desktop\\DataVisualizer\\gg\\laodanum","r");
    fscanf(fil1, "%lf", &imagenumber1);
    fscanf(fil2, "%lf", &imagenumber2);
    jmp = 100.00 / (imagenumber1+imagenumber2-1);
    val = 0;

}

showqianzhi::~showqianzhi()
{
    delete ui;
}


int showqianzhi::showimage(int i)
{
    char tmp[64];
    sprintf(tmp,"%d",i);
    QString t =tmp;
    QString s = path1 +t+ ".jpg";   //这里是绝对路径，灰常重要
    QImage* img=new QImage;
    std:: cout << s.toStdString() << std :: endl;
    if(img->load(s))
        ui->label->setPixmap(QPixmap::fromImage(*img));         //important:图像显示在label上
    else
        return 1;
    return 0;
}

void showqianzhi::showimage2(int i)
{
    char tmp[64];
    sprintf(tmp,"%d",i);
    QString t =tmp;
    QString s = path2 +t+ ".jpg";   //这里是绝对路径，灰常重要
    QImage* img=new QImage;
    if(img->load(s))
        ui->label_4->setPixmap(QPixmap::fromImage(*img));         //important:图像显示在label_4上
}

void showqianzhi::timerEvent(QTimerEvent *event)
{
    if(step < imagenumber1+imagenumber2)
    {
        singlestep();
        id = startTimer(speed);
    }
    else killTimer(id);
}

void showqianzhi::singlestep()
{
    killTimer(id);
    val += jmp;
    ui -> progressBar -> setValue(val >= 98.5 ? 100 : val);
    if(step<imagenumber1){
        path1 = "C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\out";
        path2 = "\\";
        showimage(step);
        showimage2(step);
        step++;
    }
    else if (step <(imagenumber1 + imagenumber2))
    {
        path1="C:\\Users\\x86\\Desktop\\DataVisualizer\\gg\\out";
        path2="C:\\Users\\x86\\Desktop\\DataVisualizer\\g1\\out";
        showimage(step - imagenumber1);
        showimage2(step - imagenumber1);
        step ++;
    }
    else {
        QMessageBox::warning(this, tr("Waring"),
                              tr("It has been finished"),
                              QMessageBox::Yes);
    }
}

void showqianzhi::premanentstep(int sp)
{
    speed = sp ;
    singlestep();
    id = startTimer(speed);
}

void showqianzhi::stop()
{
    killTimer(id);
}

void showqianzhi::continuestep()
{
    singlestep();
    id = startTimer(speed);
}

void showqianzhi::reset()
{
    killTimer(id);
    path1 = "C:\\Users\\x86\\Desktop\\DataVisualizer\\pics\\out";
    path2 = "\\";
    QImage *image1 = new QImage, *image2 = new QImage;
    image1->load("C:\\Users\\x86\\Pictures\\kongbai.png");
    image2->load("C:\\Users\\x86\\Pictures\\kongbai.png");
    ui->label->setPixmap(QPixmap::fromImage(*image1));
    ui->label_4->setPixmap(QPixmap::fromImage(*image2));
    //showimage(0);
    //showimage2(0);
    step = 0;
    speed = 100;
    ui -> progressBar -> setValue(0);
    val = 0;
}

void showqianzhi::setstep(int i)
{
    step = i;
    showimage(step);
    showimage2(step);
}

void showqianzhi::on_pushButton_2_clicked()
{
    singlestep();
}



void showqianzhi::on_pushButton_3_clicked()
{
    speed = ui -> horizontalSlider -> value();
    continuestep();
}

void showqianzhi::on_pushButton_clicked()
{
    stop();
}

void showqianzhi::on_pushButton_4_clicked()
{
    reset();
}

void showqianzhi::setpath(QString p1, QString p2 )
{
    path1 = p1;
    path2 = p2;
}
