#include "triggeroutputport.h"
#include "triggerinputport.h"

TriggerOutputPort::TriggerOutputPort(Node* node, QString name, QString tooltip)
    : OutputPort(node, name, tooltip, Trigger)
{
}

void TriggerOutputPort::trigger() const
{
    for (InputPort* in : targets()) {
        Q_ASSERT(in->type() == Trigger);
        ((TriggerInputPort*) in)->trigger();
    }
}
