#include "counternode.h"
#include "Settings/integersetting.h"

REGISTER_DEFN_NODETYPE(CounterNode);

CounterNode::CounterNode(QDataStream& stream) : Node(stream)
{
    setName("Counter");

    addPort(new TriggerInputPort(this, "Clock", ""));
    addPort(new TriggerInputPort(this, "Reset", ""));
    addPort(new TriggerOutputPort(this, "Overflow", ""));
    addPort(new DataInputPort(this, "Count to", "", false));
    addPort(new DataOutputPort(this, "Count", ""));

    addSetting(new IntegerSetting(this, "Count to", "", 1, 10000, 5, 5, true));
    setting<IntegerSetting>("Count to")->connectPort(dataInputPort("Count to"));
}

void CounterNode::trigger(const TriggerInputPort* in)
{
    if (in == triggerInputPort("Clock")) {
        _currentCount++;
        if (_currentCount >= dataInputPort("Count to")->data().value<int>()) {
            _currentCount = 0;
            triggerOutputPort("Overflow")->trigger();
        }
        dataOutputPort("Count")->setData(_currentCount);
    } else if (in == triggerInputPort("Reset")) {
        _currentCount = 0;
        dataOutputPort("Count")->setData(0);
    }
}
