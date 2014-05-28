#include "tointegernode.h"

REGISTER_DEFN_NODETYPE(ToIntegerNode);

ToIntegerNode::ToIntegerNode(QDataStream& stream)
    : EnableableNode(stream)
{
    setName("Integer");
    addSetting(new IntegerSetting(this, "Integer", "", 0, 0));
    addPort(new InputPort(this, "Value", "", Port::Scalar));
    addPort(new OutputPort(this, "Integer", "", Port::Scalar));

    setting<IntegerSetting>("Integer")->connectPort(inputPort("Value"));


    connect(inputPort("Value"), &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert<int>())
            return;
        setting<IntegerSetting>("Integer")->setValue(data.value<double>());
    });

    setting<IntegerSetting>("Integer")->connectPort(outputPort("Integer"));
}
