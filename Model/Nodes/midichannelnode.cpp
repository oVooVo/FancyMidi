#include "midichannelnode.h"
#include "../inputport.h"
#include "keyboard.h"
#include <QDebug>
#include "../datainputport.h"

MidiChannelNode::MidiChannelNode(QDataStream& stream)
    : Node(stream)
{
    addPort(new DataInputPort(this, "Channel", ""));
    addSetting(new IntegerSetting(this, "Channel", "", 0, 15, 0, 0, true));



    setting<IntegerSetting>("Channel")->connectPort(dataInputPort("Channel"));

}

int MidiChannelNode::channel() const
{
    return dataInputPort("Channel")->data().value<int>();
}
