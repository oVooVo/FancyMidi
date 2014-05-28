#include "switch.h"
#include "../inputport.h"
#include "../outputport.h"
#include "Settings/integersetting.h"

REGISTER_DEFN_NODETYPE(Switch);

const int num_inputs = 5;

Switch::Switch(QDataStream& stream) : Node(stream)
{
    setName("Switch");
    addPort(new OutputPort(this, "Value", "", Port::Scalar));
    addPort(new InputPort(this, "Key", "", Port::Scalar));

    addSetting(new IntegerSetting(this, "Key", "", 0, num_inputs - 1, 0, 0, false));
    setting<IntegerSetting>("Key")->connectPort(inputPort("Key"));

    for (int i = 0; i < num_inputs; i++) {
        InputPort* ip = new InputPort(this, QString("Input %1").arg(i), "", Port::Scalar);
        addPort(ip);
        connect(ip, &InputPort::receivedData, [this, i](QVariant data) {
            if (i == setting<IntegerSetting>("Key")->value())
                outputPort("Value")->send(data);
        });
    }
}
