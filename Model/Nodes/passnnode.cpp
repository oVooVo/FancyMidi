#include "passnnode.h"
#include "../inputport.h"
#include "../outputport.h"
#include "Settings/integersetting.h"

REGISTER_DEFN_NODETYPE(PassNNode);

PassNNode::PassNNode(QDataStream& stream) : Node(stream)
{
    setName("Pass N");
    addPort(new InputPort(this, "Value", "", Port::Scalar));
    addPort(new OutputPort(this, "Value", "", Port::Scalar));
    addPort(new InputPort(this, "Reset", "", Port::Trigger));
    addPort(new InputPort(this, "n", "", Port::Scalar));

    addSetting(new IntegerSetting(this, "n", "", 1, 1000, 2, 2, true));
    setting<IntegerSetting>("n")->connectPort(inputPort("n"));

    connect(inputPort("Value"), &InputPort::receivedData, [this](QVariant data) {
        if (_i == setting<IntegerSetting>("n")->value()) {
            _i = 0;
            outputPort("Value")->send(data);
        }
        _i++;
    });

    connect(inputPort("Reset"), &InputPort::receivedData, [this]() {
        _i = 0;
    });

}
