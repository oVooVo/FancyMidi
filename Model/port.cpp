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


Node* Port::getNode() const
{
	return _node;
}

QString Port::getName() const
{
    return _name;
}

QString Port::getInfoText() const
{
    return _infoText;
}

Port::Type Port::type() const
{
    return _type;
}











