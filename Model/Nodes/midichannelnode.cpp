#include "midichannelnode.h"
#include "../inputport.h"
#include "keyboard.h"
#include <QDebug>

MidiChannelNode::MidiChannelNode(QPoint position, Project* parent, QString name, QString tooltip)
    : EnableableNode(position, parent, name, tooltip)
{
    addPort(new InputPort(this, "Channel", "midi channel", Port::Scalar));
    addSetting(new IntegerSetting(this, "Channel", "", 0, Keyboard::NUM_MIDI_CHANNELS - 1, 0, 0));

    connect(inputPort("Channel"), &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert(QVariant::Int)) return;

        setting<IntegerSetting>("Channel")->setValue(data.value<int>());
    });
}

void MidiChannelNode::setChannel(int channel)
{
    setting<IntegerSetting>("Channel")->setValue(channel);
}
