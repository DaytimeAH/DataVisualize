#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QFile>
#include <QTextStream>
#include <QString>

class FileHandler
{
public:
    FileHandler(QString _path = "in.txt");
    void changePath(QString newPath);
    QList<QString> getNames();
    QList<QList<bool> > getAdj();
private:
    void read();
    void processLine(QString line);
    void processFile();
    void createMatrix();
    int lineLength;
    bool done;
    QList<QList<bool> > adjacency;
    QList<QString> text;
    QList<QString> names;
    QList<int>     IDs;
    QString path;
};

#endif // FILEHANDLER_H
