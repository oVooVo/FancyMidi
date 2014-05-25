#include "memorynode.h"
#include "../inputport.h"
#include "../outputport.h"
#include "Settings/integersetting.h"
#include "Settings/arbitrarydoublesetting.h"

REGISTER_DEFN_NODETYPE(MemoryNode);

MemoryNode::MemoryNode(QPoint position, Project* parent) : Node(position, parent, "Memory")
{
    addPort(new InputPort(this, "Write Key", "", Port::Scalar));
    addPort(new InputPort(this, "Write Value", "", Port::Scalar));
    addPort(new InputPort(this, "Write", "", Port::Trigger));
    addPort(new InputPort(this, "Read Key", "", Port::Scalar));
    addPort(new InputPort(this, "Read", "", Port::Trigger));
    addPort(new OutputPort(this, "Value", "", Port::Scalar));

    connect(inputPort("Read"), SIGNAL(receivedData(QVariant)), this, SLOT(read()));
    connect(inputPort("Write"), SIGNAL(receivedData(QVariant)), this, SLOT(write()));

    connect(inputPort("Read Key"), &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert<int>())
            return;
        _readKey = data.value<int>();
    });

    connect(inputPort("Write Key"), &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert<int>())
            return;
        _writeKey = data.value<int>();
    });

    connect(inputPort("Write Value"), &InputPort::receivedData, [this](QVariant data) {
        _writeValue = data;
    });

}

void MemoryNode::write()
{
    _data.insert(_writeKey, _writeValue);
}

void MemoryNode::read()
{
    outputPort("Value")->send(_data.value(_readKey));
}
