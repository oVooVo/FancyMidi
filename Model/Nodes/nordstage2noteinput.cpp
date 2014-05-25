#include "nordstage2noteinput.h"
#include "nordstage2.h"
#include <QDebug>

REGISTER_DEFN_NODETYPE(NordStage2NoteInput);

NordStage2NoteInput::NordStage2NoteInput(QPoint position, Project* parent)
    : MidiChannelNode(position, parent, "Note Input")
{
    addPort(new OutputPort(this, "Note On", "", Port::Trigger));
    addPort(new OutputPort(this, "Note Off", "", Port::Trigger));
    addPort(new OutputPort(this, "Velocity", "", Port::Scalar));
    addPort(new OutputPort(this, "Note", "", Port::Scalar));

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
            outputPort("Velocity")->send(data.value<int>());
        outputPort("Note")->send(key.code());
    }
    if (key.type() == MidiKey::NoteOff)
        outputPort("Note Off")->send();
    else if (key.type() == MidiKey::NoteOn)
        outputPort("Note On")->send();
}

