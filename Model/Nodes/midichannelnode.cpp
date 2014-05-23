#include "midichannelnode.h"
#include "../inputport.h"

MidiChannelNode::MidiChannelNode(QPoint position, Project* parent, QString name, QString tooltip)
    : Node(position, parent, name, tooltip)
{
    _inputs += new InputPort(this, "channel", "midi channel", Port::Scalar);
    _channelSetting = new IntegerSetting(this, "Channel", "", 0, 15, 0, 1, 0);

    connect(_inputs[0], &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert(QVariant::Int)) return;

        _channelSetting->setValue(data.value<int>());
    });
}

void MidiChannelNode::setChannel(int channel)
{
    _channelSetting->setValue(channel);
}
