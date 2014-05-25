#include "enableablenode.h"
#include "../inputport.h"
#include "Settings/integersetting.h"

EnableableNode::EnableableNode(QDataStream& stream)
    : Node(stream)
{
    addPort(new InputPort(this, "Enabled", "", Port::Scalar));
    addPort(new OutputPort(this, "Enabled", "", Port::Scalar));

    addSetting(new BoolSetting(this, "Enabled", "", true, true));

    setting<BoolSetting>("Enabled")->connectPort(inputPort("Enabled"));
    setting<BoolSetting>("Enabled")->connectPort(outputPort("Enabled"));

    connect(setting<BoolSetting>("Enabled"), &BoolSetting::changed, [this]() {
        setBlock(!setting<BoolSetting>("Enabled")->value());
    });
}
