#include "timernode.h"
#include "../outputport.h"
#include <QTimer>
#include <QDebug>

REGISTER_DEFN_NODETYPE(TimerNode);

TimerNode::TimerNode(QDataStream &stream)
    : Node(stream)
{
    setName("Timer");
    registerTimer(&_timer);

    addPort(new TriggerOutputPort(this, "Timeout", ""));
    addPort(new TriggerInputPort(this, "Stop", "Stops the timer"));
    addPort(new TriggerInputPort(this, "Start", "Starts the timer"));
    addPort(new DataInputPort(this, "Interval", ""));

    addSetting(new IntegerSetting(this, "Interval", "", 1, 100));

    setting<IntegerSetting>("Interval")->connectPort(dataInputPort("Interval"));

    connect(&_timer, &QTimer::timeout, [this]() {
        triggerOutputPort("Timeout")->trigger();
    });
}

void TimerNode::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Stop"))
        _timer.stop();
    else if (in == triggerInputPort("Start")) {
        _timer.start(dataInputPort("Interval")->data().value<int>());
    }
}

void TimerNode::notify(const DataInputPort *in, const QVariant& data)
{
    if (in == dataInputPort("Interval")) {
        _timer.setInterval(data.value<int>());
    }
}


