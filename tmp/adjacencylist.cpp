#include "adjacencylist.h"
#include <QString>

AdjacencyList::AdjacencyList()
{
    head = new Node(0);
}

void AdjacencyList::First()
{
    current = head->next;
}

AdjacencyList::Node* AdjacencyList::Current() const
{
    return current;
}

void AdjacencyList::Next()
{
    current = current->next;
}

void AdjacencyList::Insert(const int &value, const int& weight)
{
    Node* current = head;
    while (current->next != 0)
    {
        current = current->next;
    }

    current->next = new Node(value);
    current->next->Weight = weight;
}

QString AdjacencyList::printValues()
{
    Node* locCurrent = head;
    QString line;
    while(locCurrent->next != 0)
    {
        line.append(QString::number(locCurrent->next->Dest+1) + " ");
        locCurrent = locCurrent->next;
    }
    return line;

}
