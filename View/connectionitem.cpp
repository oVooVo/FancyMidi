#include "connectionitem.h"

#include <QPainter>
#include "Model/abstractgraphscene.h"

#include <QDebug>

#define WIDTH 2

ConnectionItem::ConnectionItem(PortItem *outputPort, PortItem *inputPort, bool selectable, QGraphicsScene* scene, QGraphicsPathItem *parent) :
    QGraphicsPathItem(parent)
{
    scene->addItem(this);
    _inputPort = inputPort;
    _outputPort = outputPort;

    if (selectable) {
        setFlag(QGraphicsItem::ItemIsSelectable);
    }

    setPen(QPen(Qt::black, WIDTH));
    setBrush(Qt::NoBrush);
    setZValue(-1);

    inputPort->addConnectionItem(this);
    outputPort->addConnectionItem(this);

    updatePath();
}

ConnectionItem::~ConnectionItem()
{
    inputPort()->removeConnectionItem(this);
    outputPort()->removeConnectionItem(this);
}

void ConnectionItem::updatePath()
{
    qreal easeX = 0.25;
    qreal easeY = 0;
    QPainterPath p;

    QPointF pos1(_inputPort->scenePos());
    QPointF pos2(_outputPort->scenePos());

    p.moveTo(pos1);

    qreal dx = pos2.x() - pos1.x();
    qreal dy = pos2.y() - pos1.y();

    QPointF ctr1(pos1.x() + dx * easeX, pos1.y() + dy * easeY);
    QPointF ctr2(pos1.x() + dx * (1-easeX), pos1.y() + dy * (1-easeY));

    p.cubicTo(ctr1, ctr2, pos2);

    setPath(p);
}

PortItem* ConnectionItem::outputPort()
{
    return _outputPort;
}

PortItem* ConnectionItem::inputPort()
{
    return _inputPort;
}

void ConnectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen;
    pen.setWidth(WIDTH);
    if (isSelected()) {
        pen.setColor(Qt::darkYellow);
    } else {
        pen.setColor(Qt::black);
    }
    painter->setPen(pen);
    painter->drawPath(path());
}




