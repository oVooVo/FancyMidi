#include "delaynode.h"
#include "Settings/integersetting.h"
#include "../triggeroutputport.h"
#include "../dataoutputport.h"
#include <QTimer>

REGISTER_DEFN_NODETYPE(DelayNode);

DelayNode::DelayNode(QDataStream& stream)
    : Node(stream)
{
    setName("Delay");

    addPort(new TriggerInputPort(this, "Trigger", ""));
    addPort(new DataInputPort(this, "Data", ""));
    addPort(new TriggerOutputPort(this, "Trigger", ""));
    addPort(new DataOutputPort(this, "Data", ""));
    addPort(new DataInputPort(this, "Delay", "", false));

    addSetting(new BoolSetting(this, "Synchronize", "", true, true));
    addSetting(new IntegerSetting(this, "Delay", "", 0, 10000, 500, 0));

    setting<IntegerSetting>("Delay")->connectPort(dataInputPort("Delay"));

}

void DelayNode::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Trigger")) {
        QTimer* timer = new QTimer(this);
        timer->setSingleShot(true);
        QVariant data = dataInputPort("Data")->data();
        connect(timer, &QTimer::timeout, [data, this, timer]() {
            if (setting<BoolSetting>("Synchronize")->value())
                dataOutputPort("Data")->setData(data);

            triggerOutputPort("Trigger")->trigger();
            timer->deleteLater();
        });
        timer->start(dataInputPort("Delay")->data().value<int>());
    }
}

void DelayNode::notify(const DataInputPort *in, const QVariant &data)
{
    if (in == dataInputPort("Data")) {
        if (setting<BoolSetting>("Synchronize")->value())
            return;

        QTimer* timer = new QTimer(this);
        timer->setSingleShot(true);
        connect(timer, &QTimer::timeout, [data, this, timer]() {
            dataOutputPort("Data")->setData(data);
            timer->deleteLater();
        });
        timer->start(dataInputPort("Delay")->data().value<int>());
    }
}

