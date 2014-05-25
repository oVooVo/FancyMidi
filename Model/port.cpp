#include <QDebug>
#include "port.h"

Port::Port(Node* node, QString name, QString infoText, Type type)
{
	_node = node;
    _name = name;
    _infoText = infoText;
    _type = type;
}

Port::~Port()
{

}

Node* Port::node() const
{
	return _node;
}

QString Port::name() const
{
    return _name;
}

QString Port::infoText() const
{
    return _infoText;
}

bool Port::canConnect(const Port *port1, const Port *port2)
{
    //TODO check cycles
    Q_UNUSED(port1);
    Q_UNUSED(port2);
    return true;
}










