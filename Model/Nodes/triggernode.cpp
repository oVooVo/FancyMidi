#include "triggernode.h"
#include "Settings/triggersetting.h"
#include "../triggeroutputport.h"

REGISTER_DEFN_NODETYPE(TriggerNode);

TriggerNode::TriggerNode(QDataStream& stream) : Node(stream)
{
    setName("Trigger");
    addSetting(new TriggerSetting(this, "Trigger", "", true));
    addPort(new TriggerOutputPort(this, "Trigger", ""));

    connect(setting<TriggerSetting>("Trigger"), &TriggerSetting::changed, [this]() {
        triggerOutputPort("Trigger")->trigger();
    });
}
