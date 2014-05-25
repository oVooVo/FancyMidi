#include "timernode.h"
#include "../outputport.h"
#include <QTimer>
#include <QDebug>

REGISTER_DEFN_NODETYPE(TimerNode);

TimerNode::TimerNode(QDataStream &stream)
    : EnableableNode(stream)
{
    setName("Timer");
    addSetting(new IntegerSetting(this, "Duration", "Interval", 0, 10000, 1000, 1000));
    addSetting(new IntegerSetting(this, "Intervall", "Interval", 0, 10000, 1000, 1000));
    addPort(new OutputPort(this, "Timeout", "", Port::Trigger));
    addPort(new OutputPort(this, "Time", "", Port::Scalar));
    addPort(new InputPort(this, "Stop", "Stops the timer", Port::Trigger));
    addPort(new InputPort(this, "Start", "Starts the timer", Port::Trigger));
    addPort(new InputPort(this, "Reset", "Synchronizes the timer", Port::Trigger));
    addPort(new InputPort(this, "Duration", "", Port::Scalar));
    addPort(new InputPort(this, "Intervall", "", Port::Scalar));

    setting<IntegerSetting>("Duration")->connectPort(inputPort("Duration"));
    setting<IntegerSetting>("Intervall")->connectPort(inputPort("Intervall"));


    connect(setting<IntegerSetting>("Intervall"), &IntegerSetting::changed, [this]() {
        _timer.setInterval(setting<IntegerSetting>("Intervall")->value());
    });

    connect(&_timer, &QTimer::timeout, [this]() {
       outputPort("Time")->send(_time);
       _time++;
       if (_time >= setting<IntegerSetting>("Duration")->value()) {
           _time = 0;
           outputPort("Timeout")->send();
       }
    });

    connect(inputPort("Stop"), &InputPort::receivedData, [this]() {
        _timer.stop();
    });

    connect(inputPort("Start"), &InputPort::receivedData, [this]() {
        if (!_timer.isActive())
            _timer.start();
    });

    connect(inputPort("Reset"), &InputPort::receivedData, [this]() {
        _time = 0;
    });

    _timer.start(setting<IntegerSetting>("Intervall")->value());
}


