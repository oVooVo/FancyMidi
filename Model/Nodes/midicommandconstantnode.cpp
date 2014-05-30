#include "midicommandconstantnode.h"
#include "Settings/midicommandselectsetting.h"

REGISTER_DEFN_NODETYPE(MidiCommandConstantNode);

MidiCommandConstantNode::MidiCommandConstantNode(QDataStream &stream) : Node(stream)
{
    addSetting(new MidiCommandSelectSetting(this, "Command", ""));
    addPort(new DataOutputPort(this, "Category", ""));
    addPort(new DataOutputPort(this, "Property", ""));
    addPort(new DataOutputPort(this, "Data", ""));
}

void MidiCommandConstantNode::updateData(const DataOutputPort *) const
{
    MidiCommandSelectSetting* mcss = setting<MidiCommandSelectSetting>("Command");
    //dataOutputPort("Channel")->setData(mcss->channel());
    dataOutputPort("Category")->setData(mcss->currentCategory());
    dataOutputPort("Property")->setData(mcss->currentProperty());
    dataOutputPort("Data")->setData(mcss->value());
}
