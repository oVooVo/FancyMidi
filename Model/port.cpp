#include <QDebug>
#include "port.h"

#include "outputport.h"
#include "inputport.h"

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
    const OutputPort* out = (const OutputPort*) (port1->isInput() ? port2 : port1);
    const InputPort*  in  = (const InputPort*)  (port1->isInput() ? port1 : port2);

    return !out->closesCycle(in) && (out->type() == Data || in->type() == Trigger);
}








