#include "triggerinputport.h"
#include "Nodes/node.h"

TriggerInputPort::TriggerInputPort(Node *node, QString name, QString tooltip)
    : InputPort(node, name, tooltip, Trigger, true)
{

}

void TriggerInputPort::trigger()
{
    node()->trigger(this);
    emit blink();
}
