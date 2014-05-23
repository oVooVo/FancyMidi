#include "triggernode.h"
#include "../outputport.h"
#include <QTimer>
#include <QDebug>

REGISTER_DEFN_NODETYPE(TriggerNode);

TriggerNode::TriggerNode(QPoint position, Project* parent) : Node(position, parent, "Trigger")
{
    _timeOutSetting = new IntegerSetting(this, "Interval", "Interval", 0, 10000, 1000, 1, 1000);
    _outputs += new OutputPort(this, "", "Trigger", Port::Trigger);
    _inputs += new InputPort(this, "Stop", "Stops the timer", Port::Trigger);
    _inputs += new InputPort(this, "Start", "Starts the timer", Port::Trigger);
    _inputs += new InputPort(this, "Enabled", "Enables or disables the timer", Port::Bool);


    connect(&_timer, &QTimer::timeout, [this]() {
        _outputs[0]->send(0);
    });

    connect(_timeOutSetting, &IntegerSetting::changed, [this]() {
        _timer.setInterval(_timeOutSetting->value());
    });

    connect(_inputs[0], &InputPort::receivedData, [this]() {
        _timer.stop();
    });

    connect(_inputs[1], &InputPort::receivedData, [this]() {
        _timer.start();
    });

    _timer.start(_timeOutSetting->value());
}


