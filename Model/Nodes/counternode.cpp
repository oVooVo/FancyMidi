#include "counternode.h"
#include "../inputport.h"
#include "../outputport.h"
#include "Settings/integersetting.h"

REGISTER_DEFN_NODETYPE(CounterNode);

CounterNode::CounterNode(QDataStream& stream) : Node(stream)
{
    setName("Counter");
    addPort(new InputPort(this, "Clock", "", Port::Trigger));
    addPort(new InputPort(this, "Reset", "", Port::Trigger));
    addPort(new InputPort(this, "Count to", "", Port::Scalar));
    addPort(new OutputPort(this, "Count", "", Port::Scalar));
    addPort(new OutputPort(this, "Overflow", "", Port::Trigger));

    addSetting(new IntegerSetting(this, "Count to", "", 0, 1000, 1, 1, true));

    setting<IntegerSetting>("Count to")->connectPort(inputPort("Count to"));

    connect(inputPort("Clock"), &InputPort::receivedData, [this]() {
        _currentCount++;
        if (_currentCount >= setting<IntegerSetting>("Count to")->value()) {
            outputPort("Overflow")->send();
            _currentCount = 0;
        }
        outputPort("Count")->send(_currentCount);
    });

    connect(inputPort("Reset"), &InputPort::receivedData, [this]() {
        outputPort("Count")->send(_currentCount);
    });

}
