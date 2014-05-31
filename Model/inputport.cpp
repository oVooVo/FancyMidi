#include <QDebug>
#include "inputport.h"
#include "outputport.h"
#include "Nodes/node.h"
#include "port.h"
#include <QTimer>

InputPort::InputPort(Node* node, QString name, QString infoText, Type type, bool canNotify): Port(node, name, infoText, type)
{
	_source = NULL;
    _canNotify = canNotify;
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
            emit connectionToggled(false);
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
            on_connect(port);
            emit connectionToggled(true);
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

OutputPort* InputPort::source() const
{
    return _source;
}












