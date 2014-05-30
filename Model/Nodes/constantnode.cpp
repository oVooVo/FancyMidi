#include "constantnode.h"
#include "Settings/doublesetting.h"

REGISTER_DEFN_NODETYPE(ConstantNode);

ConstantNode::ConstantNode(QDataStream &stream) : Node(stream)
{
    addPort(new DataOutputPort(this, "Value", ""));
    addSetting(new DoubleSetting(this, "Value", "", 0, 0, true));


    connect(setting<DoubleSetting>("Value"), &DoubleSetting::changed, [this]() {
        dataOutputPort("Value")->setData(setting<DoubleSetting>("Value")->value());
    });
}
