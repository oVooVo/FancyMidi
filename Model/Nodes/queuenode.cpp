#include "queuenode.h"
#include "../dataoutputport.h"

REGISTER_DEFN_NODETYPE(QueueNode);

QueueNode::QueueNode(QDataStream &stream) : Node(stream)
{
    addPort(new DataInputPort(this, "Enqueue", "", false));
    addPort(new DataOutputPort(this, "Dequeue", ""));
    addPort(new TriggerInputPort(this, "Clock", ""));
}

void QueueNode::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Clock")) {
        dataOutputPort("Dequeue")->setData(_datum);
        _datum = dataInputPort("Enqueue")->data();
    }
}
