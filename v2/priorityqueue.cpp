#include "priorityqueue.h"

PriorityQueue::PriorityQueue()
{
}

void PriorityQueue::enqueue(int weight, int dest)
{
    for (int i = 0; i < queue.count(); ++i) {
        if (weight < queue[i].first) {
            queue.insert(i,QPair<int,int>(weight,dest));
            return;
        }
    }
    queue.append(QPair<int,int>(weight, dest));
}

int PriorityQueue::dequeue()
{
    return queue.dequeue().second;
}

int PriorityQueue::count()
{
    return queue.count();
}

void PriorityQueue::empty()
{
    queue.clear();
}

void PriorityQueue::replace(int weight, int node)
{
    QPair<int,int> toInsert(weight, node);
    for (int i = 0; i < queue.count(); ++i) {
        if (queue[i] == toInsert) {
            queue.replace(i, toInsert);
        }
    }
}
