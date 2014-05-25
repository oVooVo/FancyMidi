#include "persistentnode.h"
#include "../inputport.h"
#include "../outputport.h"

REGISTER_DEFN_NODETYPE(PersistentNode);

PersistentNode::PersistentNode(QDataStream &stream)
    : EnableableNode(stream)
{
    setName("Persistent");
    addPort(new InputPort(this, "On", "", Port::Trigger));
    addPort(new InputPort(this, "Off", "", Port::Trigger));
    addPort(new OutputPort(this, "Value", "", Port::Scalar));

    addSetting(new BoolSetting(this, "Value", "", false, false));
    setting<BoolSetting>("Value")->connectPort(outputPort("Value"));

    connect(inputPort("On"), &InputPort::receivedData, [this]() {
        _boolSetting->setValue(true);
    });
    connect(inputPort("Off"), &InputPort::receivedData, [this]() {
        _boolSetting->setValue(false);
    });
}

