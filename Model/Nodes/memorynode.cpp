#include "memorynode.h"
#include "../inputport.h"
#include "../outputport.h"

REGISTER_DEFN_NODETYPE(MemoryNode);

MemoryNode::MemoryNode(QDataStream& stream) : Node(stream)
{
    setName("Memory");
    addPort(new InputPort(this, "Write", "", Port::Scalar));
    addPort(new InputPort(this, "Read", "", Port::Trigger));
    addPort(new OutputPort(this, "Value", "", Port::Scalar));

    connect(inputPort("Write"), &InputPort::receivedData, [this](QVariant data) {
        _data = data;
    });

    connect(inputPort("Read"), &InputPort::receivedData, [this]() {
       outputPort("Value")->send(_data);
    });
}
