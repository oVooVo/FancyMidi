#include "passonlychanges.h"
#include "../inputport.h"
#include "../outputport.h"

REGISTER_DEFN_NODETYPE(PassOnlyChanges);

PassOnlyChanges::PassOnlyChanges(QDataStream& stream) : Node(stream)
{
    addPort(new InputPort(this, "Input", "", Port::Scalar));
    addPort(new OutputPort(this, "Output", "", Port::Scalar));

    connect(inputPort("Input"), &InputPort::receivedData, [this](QVariant data) {
        if (_data == data)
            return;

        _data = data;
        outputPort("Output")->send(_data);
    });
}
