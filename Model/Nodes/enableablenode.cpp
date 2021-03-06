#include "enableablenode.h"
#include "../inputport.h"
#include "Settings/integersetting.h"

EnableableNode::EnableableNode(QDataStream& stream)
    : Node(stream)
{
    addPort(new InputPort(this, "Enabled", "", Port::Scalar));

    addSetting(new BoolSetting(this, "Enabled", "", true, true, false));

    setting<BoolSetting>("Enabled")->connectPort(inputPort("Enabled"));

    connect(setting<BoolSetting>("Enabled"), &BoolSetting::changed, [this]() {
        setBlock(!setting<BoolSetting>("Enabled")->value());
    });
}
