#include "pitchbendinput.h"
#include "../Nodes/node.h"
#include "keyboard.h"
#include "nordstage2.h"
#include "../triggeroutputport.h"
#include "../dataoutputport.h"

REGISTER_DEFN_NODETYPE(PitchBendInput);

PitchBendInput::PitchBendInput(QDataStream &stream)
    : MidiChannelNode(stream)
{
    setName("Pitch Bend In");
    addPort(new DataOutputPort(this, "Pitch", ""));
    addPort(new TriggerOutputPort(this, "Trigger", ""));

    _connectedChannel = channel();
    connect(NordStage2::channel(channel()), SIGNAL(midiInput(int,MidiKey,QVariant)),
            this, SLOT(filter(int,MidiKey,QVariant)));

}

void PitchBendInput::filter(int channel, MidiKey key, QVariant data)
{
    Q_UNUSED(channel);
    if (key.type() == MidiKey::PitchBend) {
        dataOutputPort("Pitch")->setData(data.value<double>());
        triggerOutputPort("Trigger")->trigger();
    }
}

void PitchBendInput::notify(const DataInputPort *in, const QVariant &data)
{
    if (in == dataInputPort("Channel")) {
        disconnect(NordStage2::channel(_connectedChannel), SIGNAL(midiInput(int,MidiKey,QVariant)),
                   this, SLOT(filter(int,MidiKey,QVariant)));
        _connectedChannel = data.value<int>();
        connect(NordStage2::channel(data.value<int>()), SIGNAL(midiInput(int,MidiKey,QVariant)),
                   this, SLOT(filter(int,MidiKey,QVariant)));
    }
}
