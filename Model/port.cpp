#include <QDebug>
#include "port.h"

Port::Port(Node* node, QString name, QString infoText, bool isData = false)
{
	_node = node;
    _name = name;
    _infoText = infoText;
    _isData = isData;
}

Port::~Port()
{

}


Node* Port::getNode()
{
	return _node;
}

QString Port::getName()
{
    return _name;
}

QString Port::getInfoText()
{
    return _infoText;
}

bool Port::isData() {
    return _isData;
}











