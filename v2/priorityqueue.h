#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <QQueue>
#include <QPair>

class PriorityQueue
{
public:
    PriorityQueue();
    void enqueue(int weight, int dest);
    int dequeue();
    int count();
    void empty();
    void replace(int weight, int node);

private:
    QQueue<QPair<int,int> > queue;

};

#endif // PRIORITYQUEUE_H
