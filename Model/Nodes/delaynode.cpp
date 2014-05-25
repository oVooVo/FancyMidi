#include "delaynode.h"
#include <QTimer>

REGISTER_DEFN_NODETYPE(DelayNode);

DelayNode::DelayNode(QPoint point, Project* parent)
    : EnableableNode(point, parent, "Delay", "")
{
    addPort(new InputPort(this, "Delay", "", Port::Scalar));
    addPort(new InputPort(this, "Input", "", Port::Scalar));
    addPort(new OutputPort(this, "Output", "", Port::Scalar));
    addSetting(new IntegerSetting(this, "Delay", "", 0, 10000, 500, 0));
    setting<IntegerSetting>("Delay")->connectPort(inputPort("Delay"));

    connect(inputPort("Input"), &InputPort::receivedData, [this](QVariant data) {
        QTimer* timer = new QTimer(this);
        timer->setSingleShot(true);
        connect(timer, &QTimer::timeout, [data, this, timer]() {
            outputPort("Output")->send(data);
            timer->deleteLater();
        });
        timer->start(setting<IntegerSetting>("Delay")->value());
    });
}
