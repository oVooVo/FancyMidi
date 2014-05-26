#include "conditionnode.h"
#include "../inputport.h"
#include "../outputport.h"
#include "Settings/boolsetting.h"

REGISTER_DEFN_NODETYPE(ConditionNode);

ConditionNode::ConditionNode(QDataStream &stream) : Node(stream)
{
    setName("Conditional Pass");
    addPort(new InputPort(this, "Pass", "", Port::Scalar));
    addPort(new InputPort(this, "Value", "", Port::Scalar));
    addPort(new OutputPort(this, "Value", "", Port::Scalar));

    addSetting(new BoolSetting(this, "Pass", "", true, true));
    setting<BoolSetting>("Pass")->connectPort(inputPort("Pass"));
    connect(inputPort("Value"), &InputPort::receivedData, [this](QVariant data) {
        if (setting<BoolSetting>("Pass")->value())
            outputPort("Value")->send(data);
    });
}
