#include "triggernode.h"
#include "../outputport.h"
#include <QTimer>
#include <QDebug>

REGISTER_DEFN_NODETYPE(TriggerNode);

TriggerNode::TriggerNode(QPoint position, Project* parent) : Node(position, parent, "Trigger")
{
    _durationSetting = new IntegerSetting(this, "Duration", "Interval", 0, 10000, 1000, 1, 1000);
    _intervallSetting = new IntegerSetting(this, "Intervall", "Interval", 0, 10000, 1000, 1, 1000);
    _outputs += new OutputPort(this, "slow", "Trigger", Port::Trigger);
    _outputs += new OutputPort(this, "fast", "Trigger", Port::Trigger);
    _outputs += new OutputPort(this, "time", "time", Port::Scalar);
    _inputs += new InputPort(this, "Stop", "Stops the timer", Port::Trigger);
    _inputs += new InputPort(this, "Start", "Starts the timer", Port::Trigger);
    _inputs += new InputPort(this, "Reset", "Synchronizes the timer", Port::Trigger);
    _inputs += new InputPort(this, "Enabled", "Enables or disables the timer", Port::Scalar);


    connect(_intervallSetting, &IntegerSetting::changed, [this]() {
        _timer.setInterval(_intervallSetting->value());
    });

    connect(&_timer, &QTimer::timeout, [this]() {
       _outputs[2]->send(_time);
       _outputs[1]->send();
       _time++;
       if (_time >= _durationSetting->value()) {
           _time = 0;
           _outputs[0]->send();
       }
    });

    connect(_inputs[0], &InputPort::receivedData, [this]() {
        _timer.stop();
    });

    connect(_inputs[1], &InputPort::receivedData, [this]() {
        if (!_timer.isActive())
            _timer.start();
    });

    connect(_inputs[1], &InputPort::receivedData, [this]() {
        _time = 0;
    });

    connect(_inputs[1], &InputPort::receivedData, [this](QVariant data) {
        if (data.canConvert(QVariant::Bool)) return;
        if (_timer.isActive() && !data.value<bool>())
            _timer.stop();
        else if (!_timer.isActive() && data.value<bool>())
            _timer.start();
    });





    _timer.start(_intervallSetting->value());
}


