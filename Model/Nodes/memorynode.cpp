#include "memorynode.h"
#include "../inputport.h"
#include "../outputport.h"
#include "../datainputport.h"
#include "../dataoutputport.h"
#include "../triggerinputport.h"


REGISTER_DEFN_NODETYPE(MemoryNode);

MemoryNode::MemoryNode(QDataStream& stream) : Node(stream)
{
    setName("Memory");
    addPort(new TriggerInputPort(this, "Write", ""));
    addPort(new TriggerInputPort(this, "Take oldest", ""));
    addPort(new TriggerInputPort(this, "Take newest", ""));
    addPort(new DataInputPort(this, "Value", "", false));
    addPort(new DataOutputPort(this, "Value", ""));

}

void MemoryNode::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Write")) {
        _datas.append(dataInputPort("Value")->data());
    } else if (in == triggerInputPort("Take oldest")) {
        dataOutputPort("Value")->setData(_datas.isEmpty() ? QVariant() : _datas.takeFirst());
    } else if (in == triggerInputPort("Take newest")) {
        dataOutputPort("Value")->setData(_datas.isEmpty() ? QVariant() : _datas.takeLast());
    }
}
