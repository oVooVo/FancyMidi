#include "outputport.h"
#include <QQueue>
#include <QApplication>
#include <QDebug>
#include "Model/project.h"


OutputPort::OutputPort(Node* node, QString name, QString infoText, Type type) : Port(node, name, infoText, type)
{

}

OutputPort::~OutputPort()
{
    foreach(InputPort* target, _targets) {
		disconnect(target);
	}
}

const QSet<InputPort*> OutputPort::getTargets()
{
    return _targets;
}

void OutputPort::pushPacket(QSharedPointer<Packet> packet) {
    // Das Packet wird verworfen wenn keine Verbindung besteht.
    if(getNode()->getProject() && getNode()->getProject()->isComplete())
		return;
	if(_targets.isEmpty()) {
		packet.clear();
	}

    QVector<InputPort*> modifier;
    QVector<InputPort*> notmodifier;
	foreach(InputPort * p, _targets)
        p->isModifying() ? modifier.append(p) : notmodifier.append(p);

    // Alle bis auf den ersten Modifizierer erhalten eine Kopie des Packets
    for(int i = 1; i < modifier.count(); i++)
        modifier[i]->pushPacket(packet->copy());

    // Wenn es keine Nicht-Modifizierer gibt erhält der erste Modifizierer das Orginal- und sonst ein Kopiepacket
    if(!modifier.isEmpty())
        modifier.first()->pushPacket(notmodifier.isEmpty() ? packet : packet->copy());

    // Die Nicht-Modifizierer erhalten alle das Orginalpacket
    foreach(InputPort *port, notmodifier)
        port->pushPacket(packet);
}

bool OutputPort::connect(Port* port) {
    if(port->isInput() && port->type() == type()) {
        if(_targets.contains((InputPort*)port)) {
            return false;
        } else 
        {
            _targets.insert((InputPort*)port);
            ((InputPort*)port)->connect(this);
            return true;
        }
    }
    else {
        return false;
    }
}
bool OutputPort::disconnect(InputPort* port) {
    if(_targets.contains(port)) {
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
