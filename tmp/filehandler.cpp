#include "filehandler.h"
#include <QStringList>
#include <QDebug>


FileHandler::FileHandler(QString _path)
{
    QFile file(_path);
    if (file.exists(_path))
    {
        path = _path;
    }
    text = QList<QString>();
    names = QList<QString>();
    adjacency = QList<QList<bool> >();
    file.close();
    done = false;
}

void FileHandler::changePath(QString newPath)
{
    path = newPath;
    done = false;
}

void FileHandler::processFile()
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QString first = file.readLine();
    qDebug() << first;

    lineLength = first.split(' ').length();
    adjacency.clear();
    for (int i = 0; i < lineLength; ++i) {
        adjacency.push_back(QList<bool>());
        for (int j = 0; j < lineLength; ++j) {
            adjacency[i].push_back(false);
        }
    }

    names.append(first.split(' '));
    while (!file.atEnd())
    {
        QString line = file.readLine();
        processLine(line);
    }
}

void FileHandler::processLine(QString line)
{
    qDebug() << line;
    QList<QString> fields = line.split(' ');
    IDs.push_back(fields[0].toInt());
    for (int i = 2; i < fields.length(); ++i) {
        qDebug() << fields[i].toInt() -1  << " " << IDs.last() -1 ;
        adjacency[IDs.last()-1][fields[i].toInt()-1] = true;
    }
}

void FileHandler::createMatrix()
{
    int textInd = 0;
    for (int i = 0; i < lineLength; ++i)
    {
        for (int j = 0; j < lineLength; ++j)
        {
            adjacency[i].push_back(text[textInd++].toInt());
        }
    }
    done = true;
}

QList<QString> FileHandler::getNames()
{
    if (!done)
        processFile();

    return names;
}

QList<QList<bool> > FileHandler::getAdj()
{
    if(!done)
        processFile();

    return adjacency;
}
