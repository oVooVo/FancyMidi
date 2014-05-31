#include "conditionalpass.h"
#include "../dataoutputport.h"
#include "../triggeroutputport.h"

REGISTER_DEFN_NODETYPE(ConditionalPass);

ConditionalPass::ConditionalPass(QDataStream &stream) : Node(stream)
{
    setName("Conditional Pass");
    addPort(new DataInputPort(this, "Condition", "", false));
    addPort(new TriggerInputPort(this, "Trigger", ""));
    addPort(new DataInputPort(this, "Data", ""));
    addPort(new TriggerOutputPort(this, "Trigger Pass", ""));
    addPort(new DataOutputPort(this, "Data Pass", ""));
}

void ConditionalPass::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Trigger")) {
        if (pass()) {
            triggerOutputPort("Trigger Pass")->trigger();
        }
    }
}

void ConditionalPass::notify(const DataInputPort *in, const QVariant &data)
{
    if (in == dataInputPort("Data")) {
        if (pass()) {
            dataOutputPort("Data Pass")->setData(data);
        }
    }
}

bool ConditionalPass::pass() const
{
    return dataInputPort("Condition")->data().value<bool>();
}
