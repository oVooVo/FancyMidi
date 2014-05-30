#include "triggerinputport.h"
#include "Nodes/node.h"

TriggerInputPort::TriggerInputPort(Node *node, QString name, QString tooltip)
    : InputPort(node, name, tooltip, Trigger)
{

}

void TriggerInputPort::trigger() const
{
    node()->trigger(this);
}
