#include "rangenode.h"
#include "../inputport.h"
#include "../outputport.h"
#include "Settings/doublesetting.h"
#include "Settings/boolsetting.h"

REGISTER_DEFN_NODETYPE(RangeNode);

RangeNode::RangeNode(QDataStream &stream) : Node(stream)
{
    setName("Range");
    addPort(new InputPort(this, "Value", "", Port::Scalar));
    addPort(new InputPort(this, "Min Input", "", Port::Scalar));
    addPort(new InputPort(this, "Max Input", "", Port::Scalar));
    addPort(new InputPort(this, "Min Output", "", Port::Scalar));
    addPort(new InputPort(this, "Max Output", "", Port::Scalar));
    addPort(new InputPort(this, "Trunc", "", Port::Scalar));
    addPort(new OutputPort(this, "Value", "", Port::Scalar));

    addSetting(new DoubleSetting(this, "Value", "", 0, 0, false));
    addSetting(new DoubleSetting(this, "Min Input", "", 0, 0, true));
    addSetting(new DoubleSetting(this, "Max Input", "", 1, 1, true));
    addSetting(new DoubleSetting(this, "Min Output", "", 0, 0, true));
    addSetting(new DoubleSetting(this, "Max Output", "", 1, 1, true));
    addSetting(new BoolSetting(this, "Trunc", "", false, false, true));

    setting<DoubleSetting>("Value")->connectPort(inputPort("Value"));
    setting<DoubleSetting>("Min Input")->connectPort(inputPort("Min Input"));
    setting<DoubleSetting>("Max Input")->connectPort(inputPort("Max Input"));
    setting<DoubleSetting>("Min Output")->connectPort(inputPort("Min Output"));
    setting<DoubleSetting>("Max Output")->connectPort(inputPort("Max Output"));
    setting<BoolSetting>("Trunc")->connectPort(inputPort("Trunc"));

    connect(inputPort("Value"), &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert<double>())
            return;
        double mii = setting<DoubleSetting>("Min Input")->value();
        double mai = setting<DoubleSetting>("Max Input")->value();
        double mio = setting<DoubleSetting>("Min Output")->value();
        double mao = setting<DoubleSetting>("Max Output")->value();
        bool trunc = setting<BoolSetting>("Trunc")->value();
        double value = data.value<double>();
        value -= mii;
        value /= (mai - mii);
        value *= (mao - mio);
        value += mio;
        if (trunc)
            value = qBound(mio, value, mao);
        outputPort("Value")->send(value);
    });
}
