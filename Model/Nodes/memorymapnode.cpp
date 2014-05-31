#include "memorymapnode.h"
#include "../inputport.h"
#include "../outputport.h"
#include "Settings/integersetting.h"
#include "../dataoutputport.h"
#include "../triggerinputport.h"

REGISTER_DEFN_NODETYPE(MemoryMapNode);

MemoryMapNode::MemoryMapNode(QDataStream& stream)
    : Node(stream)
{
    setName("Memory Map");
    addPort(new DataInputPort(this, "Write Key", "", false));
    addPort(new DataInputPort(this, "Write Value", "", false));
    addPort(new TriggerInputPort(this, "Write", ""));
    addPort(new DataInputPort(this, "Read Key", "", false));
    addPort(new TriggerInputPort(this, "Read", ""));
    addPort(new DataOutputPort(this, "Value", ""));
}

void MemoryMapNode::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Write")) {
        _data.insert(dataInputPort("Write Key")->data().value<int>(),
                     dataInputPort("Write Value")->data());
    } else if (in == triggerInputPort("Read")) {
        dataOutputPort("Value")->setData(_data.value(dataInputPort("Read Key")->data().value<int>(), QVariant()));
    }
}
