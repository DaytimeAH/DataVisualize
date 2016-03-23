#ifndef NODEGRAPHICSITEM_H
#define NODEGRAPHICSITEM_H


#include <QGraphicsItem>
#include <QBrush>

class NodeGraphicsItem : public QGraphicsItem
{
public:
    NodeGraphicsItem(QString str);

    QRectF boundingRect() const; // határoló téglalap
    QPainterPath shape() const; // alakzat
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // kirajzolás
    void advance(int phase); // jelenet léptetése
    void setDepthNo(int no);
    void setEndNo(int no);
    void setBrush(QBrush brush);
    bool contains(const QPointF &point) const;
    int getDepthNo() { return depthNo; }
    int getEndNo() { return endNo; }
private:
    QBrush brush;
    QColor color; // szín
    QString text;
    int    depthNo;
    int    endNo;
};

#endif // NODEGRAPHICSITEM_H
