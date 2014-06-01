#include "switch.h"
#include "../triggerinputport.h"
#include "../dataoutputport.h"
#include "../datainputport.h"
#include "Settings/integersetting.h"
#include "Settings/boolsetting.h"

REGISTER_DEFN_NODETYPE(Switch);

const int num_inputs = 5;

Switch::Switch(QDataStream& stream) : Node(stream)
{
    setName("Switch");
    addPort(new DataOutputPort(this, "Value", ""));
    addPort(new TriggerInputPort(this, "On", ""));
    addPort(new TriggerInputPort(this, "Off", ""));

    addSetting(new BoolSetting(this, "Value", "", false, false, true));

}

void Switch::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("On")) {
        setting<BoolSetting>("Value")->setValue(true);
        dataOutputPort("Value")->setData(true);
    } else if (in == triggerInputPort("Off")) {
        setting<BoolSetting>("Value")->setValue(false);
        dataOutputPort("Value")->setData(false);
    }
}
