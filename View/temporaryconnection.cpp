#include "temporaryconnection.h"
#include <QDebug>

TemporaryConnection::TemporaryConnection(PortItem* portItem, QGraphicsScene* scene, QGraphicsItem* parent) :
    QGraphicsPathItem(parent)
{
    scene->addItem(this);
    _portItem = portItem;

    setPen(QPen(Qt::lightGray, 2));
    setBrush(Qt::NoBrush);
    setZValue(-1);
    _black = false;
}

void TemporaryConnection::updatePath(QPointF position)
{
    if (_black) {
        setPen(QPen(Qt::black, 2));
    } else {
        setPen(QPen(Qt::lightGray, 2));
    }
    qreal easeX = 0.25;
    qreal easeY = 0;
    QPainterPath p;

    QPointF pos1(_portItem->scenePos());
    QPointF pos2(position);

    p.moveTo(pos1);

    qreal dx = pos2.x() - pos1.x();
    qreal dy = pos2.y() - pos1.y();

    QPointF ctr1(pos1.x() + dx * easeX, pos1.y() + dy * easeY);
    QPointF ctr2(pos1.x() + dx * (1-easeX), pos1.y() + dy * (1-easeY));

    p.cubicTo(ctr1, ctr2, pos2);

    setPath(p);
}

PortItem* TemporaryConnection::portItem()
{
    return _portItem;
}

void TemporaryConnection::setBlack()
{
    _black = true;
}

void TemporaryConnection::setGrey()
{
    _black = false;
}
