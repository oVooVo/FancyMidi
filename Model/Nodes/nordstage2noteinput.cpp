#include "nordstage2noteinput.h"
#include "nordstage2.h"
#include <QDebug>
#include "../triggeroutputport.h"
#include "../dataoutputport.h"


REGISTER_DEFN_NODETYPE(NordStage2NoteInput);

NordStage2NoteInput::NordStage2NoteInput(QDataStream &stream)
    : MidiChannelNode(stream)
{
    setName("Note Input");
    addPort(new TriggerOutputPort(this, "Note On", ""));
    addPort(new TriggerOutputPort(this, "Note Off", ""));
    addPort(new DataOutputPort(this, "Velocity", ""));
    addPort(new DataOutputPort(this, "Note", ""));

    for (int i = 0; i < Keyboard::NUM_MIDI_CHANNELS; i++) {
        connect(NordStage2::channel(i), SIGNAL(midiInput(int,MidiKey,QVariant)),
                this, SLOT(receiveMidiCommand(int,MidiKey,QVariant)));
    }
}

void NordStage2NoteInput::receiveMidiCommand(int channel, MidiKey key, QVariant data)
{
    if (channel != setting<IntegerSetting>("Channel")->value())
        return;
    if (key.type() == MidiKey::NoteOff || key.type() == MidiKey::NoteOn) {
        if (data.canConvert<int>())
            dataOutputPort("Velocity")->setData(data);
        dataOutputPort("Note")->setData(key.code());
    }
    if (key.type() == MidiKey::NoteOff)
        triggerOutputPort("Note Off")->trigger();
    else if (key.type() == MidiKey::NoteOn)
        triggerOutputPort("Note On")->trigger();
}

