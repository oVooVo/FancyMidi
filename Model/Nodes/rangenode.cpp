#include "rangenode.h"
#include "../inputport.h"
#include "../outputport.h"
#include "Settings/doublesetting.h"
#include "Settings/boolsetting.h"
#include "../dataoutputport.h"

REGISTER_DEFN_NODETYPE(RangeNode);

RangeNode::RangeNode(QDataStream &stream) : Node(stream)
{
    setName("Range");
    addPort(new DataInputPort(this, "Value", ""));
    addPort(new DataInputPort(this, "Min Input", ""));
    addPort(new DataInputPort(this, "Max Input", ""));
    addPort(new DataInputPort(this, "Min Output", ""));
    addPort(new DataInputPort(this, "Max Output", ""));
    addPort(new DataInputPort(this, "Trunc", ""));
    addPort(new DataOutputPort(this, "Value", ""));

    addSetting(new DoubleSetting(this, "Value", "", 0, 0, false));
    addSetting(new DoubleSetting(this, "Min Input", "", 0, 0, true));
    addSetting(new DoubleSetting(this, "Max Input", "", 1, 1, true));
    addSetting(new DoubleSetting(this, "Min Output", "", 0, 0, true));
    addSetting(new DoubleSetting(this, "Max Output", "", 1, 1, true));
    addSetting(new BoolSetting(this, "Trunc", "", false, false, true));

    setting<DoubleSetting>("Value")->connectPort(dataInputPort("Value"));
    setting<DoubleSetting>("Min Input")->connectPort(dataInputPort("Min Input"));
    setting<DoubleSetting>("Max Input")->connectPort(dataInputPort("Max Input"));
    setting<DoubleSetting>("Min Output")->connectPort(dataInputPort("Min Output"));
    setting<DoubleSetting>("Max Output")->connectPort(dataInputPort("Max Output"));
    setting<BoolSetting>("Trunc")->connectPort(dataInputPort("Trunc"));
}

void RangeNode::notify(const DataInputPort *in, const QVariant &)
{
    if (in == dataInputPort("Min Input") || in == dataInputPort("Max Input")
            || in == dataInputPort("Min Output") || in == dataInputPort("Max Output")
            || in == dataInputPort("Trunc") || in == dataInputPort("Value")) {
        calculate();
    } else {
        UNKNOWN_PORT;
    }
}

void RangeNode::calculate() const
{
    double mii = dataInputPort("Min Input")->data().value<double>();
    double mai = dataInputPort("Max Input")->data().value<double>();
    double mio = dataInputPort("Min Output")->data().value<double>();
    double mao = dataInputPort("Max Output")->data().value<double>();
    bool trunc = dataInputPort("Trunc")->data().value<bool>();
    double value = dataInputPort("Value")->data().value<double>();
    value -= mii;
    value /= (mai - mii);
    value *= (mao - mio);
    value += mio;
    if (trunc)
        value = qBound(mio, value, mao);
    dataOutputPort("Value")->setData(value);
}
