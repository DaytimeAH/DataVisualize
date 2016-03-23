#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <QDebug>

class AdjacencyList
{
public:
    struct Node
    {
        Node(int _value, Node* _next = 0)
        {
            Dest = _value;
            next = _next;
        }

        int Dest;
        int Weight;
        Node* next;
    };

    AdjacencyList();

    void First();
    Node* Current() const;
    void Next();

    void Insert(const int &value, const int& weight);

    QString printValues();
private:

    Node* current;
    Node* head;
};

#endif // ADJACENCYLIST_H
