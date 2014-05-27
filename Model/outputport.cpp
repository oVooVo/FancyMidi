#include "outputport.h"
#include <QQueue>
#include <QApplication>
#include <QDebug>
#include "Model/project.h"
#include <QStack>

OutputPort::OutputPort(Node* node, QString name, QString infoText, Type type)
    : Port(node, name, infoText, type)
{

}

OutputPort::~OutputPort()
{
    foreach(InputPort* target, _targets) {
		disconnect(target);
	}
}

const QSet<InputPort*> OutputPort::targets() const
{
    return _targets;
}

bool OutputPort::connect(Port* port)
{
    if(port->isInput() && canConnect(this, port)) {
        if(_targets.contains((InputPort*) port)) {
            return false;
        } else {
            _targets.insert((InputPort*) port);
            ((InputPort*) port)->connect(this);
            return true;
        }
    }
    else {
        return false;
    }
}

bool OutputPort::disconnect(InputPort* port) {
    if (_targets.contains(port)) {
        _targets.remove(port);
        port->disconnect();
        return true;
    } else {
        return false;
    }
}

bool OutputPort::isInput() const
{
    return false;
}

void OutputPort::send(QVariant data)
{
    if (_block) return;
    emit sendData(data);
    for (InputPort* ip : _targets) {
        ip->receive(data);
    }
}

void OutputPort::setBlock(bool block)
{
    _block = block;
}

bool OutputPort::closesCycle(const InputPort *in) const
{
    QStack<const Node*> toVisit;
    QSet<const Node*> visited;

    toVisit.push(node());

    while (!toVisit.isEmpty()) {
        const Node* currentNode = toVisit.pop();
        if (visited.contains(currentNode))
            continue;

        for (const InputPort* currentInput : currentNode->inputPorts()) {
            if (currentInput == in)
                return true;
            if (currentInput->source())
                toVisit.push(currentInput->source()->node());
        }
    }

    return false;
}
