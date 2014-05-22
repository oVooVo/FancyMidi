#include "portitem.h"


#include "Model/abstractgraphscene.h"
#include "nodeitem.h"
#include "connectionitem.h"

#include <QDebug>

PortItem::PortItem(Port *port, QString name, QGraphicsScene *scene, NodeItem *parent) :
    QGraphicsPathItem(parent)
{
    _label = new QGraphicsTextItem(this);
    _name = name;
    _label->setPlainText(name);

    _radius = 7;
    _margin = 2;

    QPainterPath p;
    p.addEllipse(-_radius, -_radius, 2*_radius, 2*_radius);
    setPath(p);

    _port = port;

    setPen(QPen(Qt::black, 1.5));
    if (_port && _port->isData()) {
        setBrush(Qt::darkBlue);
    } else if (_port && !_port->isData()) {
        setBrush(Qt::darkGreen);
    } else {
        setBrush(Qt::white); //no port, illegal, should never happen
    }


    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    _portFlags = 0;

}

PortItem::~PortItem()
{
    foreach (ConnectionItem* ci, _connections) {
        delete ci;
    }
}

void PortItem::setIsOutput(bool o)
{
    _isOutput = o;

    if (_isOutput)
        _label->setPos(-_radius - _margin - _label->boundingRect().width(), -_label->boundingRect().height()/2);
    else
        _label->setPos(_radius + _margin, -_label->boundingRect().height()/2);
}

int PortItem::radius()
{
    return _radius;
}

bool PortItem::isOutput()
{
    return _isOutput;
}

QVector<ConnectionItem*>& PortItem::connections()
{
    return _connections;
}

void PortItem::setPortFlags(int f)
{
    _portFlags = f;

    if (_portFlags & TypePort)
    {
        QFont font(scene()->font());
        font.setItalic(true);
        _label->setFont(font);
        setPath(QPainterPath());
    } else if (_portFlags & NamePort)
    {
        QFont font(scene()->font());
        font.setBold(true);
        _label->setFont(font);
        setPath(QPainterPath());
    }
}

NodeItem* PortItem::nodeItem() const
{
    return dynamic_cast<NodeItem*>(this->parentItem());
}

QVariant PortItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged)
    {
        foreach (ConnectionItem *conn, _connections)
        {
            conn->updatePath();
        }
    }
    return QGraphicsPathItem::itemChange(change, value);
}

Port* PortItem::port()
{
    return _port;
}

void PortItem::addConnectionItem(ConnectionItem *connectionItem)
{
    _connections.append(connectionItem);
}

void PortItem::removeConnectionItem(ConnectionItem* connectionItem)
{
    for (int i = 0; i < _connections.size(); i++) {
        if (_connections.at(i) == connectionItem) {
            _connections.remove(i);
        }
    }
}
