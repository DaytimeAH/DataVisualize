#include "nodegraphicsitem.h"

#include <qmath.h>
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include <QLinkedList>


NodeGraphicsItem::NodeGraphicsItem(QString str)
{
    brush = Qt::white;
    text = str;
    depthNo = 0;
    endNo = 0;
}

QRectF NodeGraphicsItem::boundingRect() const
{
    return QRectF(-20, -20, 70, 30);
}



QPainterPath NodeGraphicsItem::shape() const
{
    QPainterPath path;
    path.addEllipse(-20, -20, 70, 30);
    return path;
}

void NodeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::black);
    painter->setBrush(brush);
    QLineF line(this->boundingRect().bottomLeft(),this->boundingRect().topLeft());
    painter->setFont(QFont("Inconsolata", 8));
    painter->drawRect(-20, -20, 70, 30);
    painter->drawText(0,5, text);
    painter->drawText(-18,-10, QString::number(depthNo));
    painter->drawText(41,-10,QString::number(endNo));
}

void NodeGraphicsItem::advance(int phase)
{
    phase = phase +1;
}

void NodeGraphicsItem::setDepthNo(int no)
{
    depthNo = no;
}

void NodeGraphicsItem::setEndNo(int no)
{
    endNo = no;
}

void NodeGraphicsItem::setBrush(QBrush _brush)
{
    brush = _brush;
}

bool NodeGraphicsItem::contains(const QPointF &point) const
{
    qDebug() << boundingRect().x() << " " << boundingRect().y();
    return boundingRect().contains(point);
}
