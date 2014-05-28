#include "sequencenode.h"
#include "Settings/sequencesetting.h"
#include "../inputport.h"
#include "../outputport.h"

REGISTER_DEFN_NODETYPE(SequenceNode);

SequenceNode::SequenceNode(QDataStream &stream) : Node(stream)
{
    setName("Sequence Node");
    addSetting(new SequenceSetting(this, "Sequence", ""));
    addPort(new InputPort(this, "Key", "", Port::Scalar));
    addPort(new OutputPort(this, "Note", "", Port::Scalar));

    connect(inputPort("Key"), &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert<int>()) return;

        int key = data.value<int>();
        if (setting<SequenceSetting>("Sequence")->contains(key)) {
            outputPort("Note")->send(setting<SequenceSetting>("Sequence")->note(key));
        }

    });
}
