#include "simpleinputport.h"
#include "inputport.h"
#include "outputport.h"
#include "node.h"
#include "port.h"
#include <QDebug>

SimpleInputPort::SimpleInputPort(Node* node, QString name, QString infoText, Type type): InputPort(node, name, infoText, type)
{
}

void SimpleInputPort::pushPacket(QSharedPointer<Packet> packet)
{
	// TODO: fix this, filter are not the only type!
    //((Filter*)getNode())->run(packet);
}











