#include <QDebug>
#include "inputport.h"
#include "outputport.h"
#include "node.h"
#include "port.h"

InputPort::InputPort(Node* node, QString name, QString infoText, bool isData): Port(node, name, infoText, isData)
{
	_source = NULL;
}
InputPort::~InputPort() {
    disconnect();
}
bool InputPort::isModifying()
{
	return getNode()->isModifying(this);
}
bool InputPort::connect(Port* port)
{
	if(!port)
	{    // disconnect
		if(_source)
        {
			_source->disconnect(this);
            _source = NULL;
			
			return true;
		}
		else
		{
			return false;
		}
	}
	else    // connect
	{
        if(port->isInput() || port == _source || port->isData() != isData())
			return false;
		else
		{
			disconnect();

			_source = (OutputPort*)port;
			return port->connect(this);
		}
	}
}
bool InputPort::disconnect()
{
	return connect(NULL);
}
bool InputPort::isInput()
{
	return true;
}

OutputPort* InputPort::getSource() {
    return _source;
}











