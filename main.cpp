#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "stdlib.h"
#include "time.h"
#define MAX 555

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    w.setFixedSize(1350, 843);
    w.show();

    return a.exec();
}

void Ui::genRand(int *list, int count)
{
    int numRand = 0;

    srand(time(0));
    while (numRand < count)
    {
        list[numRand] = rand()%MAX;
        numRand++;
    }

}
