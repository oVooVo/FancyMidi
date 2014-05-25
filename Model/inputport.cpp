#include <QDebug>
#include "inputport.h"
#include "outputport.h"
#include "node.h"
#include "port.h"

InputPort::InputPort(Node* node, QString name, QString infoText, Type type): Port(node, name, infoText, type)
{
	_source = NULL;
}

InputPort::~InputPort()
{
    disconnect();
}

bool InputPort::connect(Port* port)
{
    if  (!port) {    // disconnect
        if (_source) {
			_source->disconnect(this);
            _source = NULL;
			
			return true;
        } else {
			return false;
		}
    } else {    // connect
        if (port->isInput() || port == _source || !canConnect(port, this))
			return false;
        else {
            disconnect();

            _source = (OutputPort*) port;
			return port->connect(this);
		}
	}
}

bool InputPort::disconnect()
{
	return connect(NULL);
}

bool InputPort::isInput() const
{
	return true;
}

OutputPort* InputPort::getSource() const
{
    return _source;
}

void InputPort::receive(QVariant data)
{
    emit receivedData(data);
}












