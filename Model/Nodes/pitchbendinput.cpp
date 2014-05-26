#include "pitchbendinput.h"
#include "../Nodes/node.h"
#include "keyboard.h"
#include "nordstage2.h"

REGISTER_DEFN_NODETYPE(PitchBendInput);

PitchBendInput::PitchBendInput(QDataStream &stream)
    : EnableableNode(stream)
{
    setName("Pitch Bend Input");
    addPort(new OutputPort(this, "Pitch", "", Port::Scalar));

    for (int i = 0; i < Keyboard::NUM_MIDI_CHANNELS; i++) {
        connect(NordStage2::channel(i), SIGNAL(midiInput(int,MidiKey,QVariant)),
                this, SLOT(filter(int,MidiKey,QVariant)));
    }
}

void PitchBendInput::filter(int channel, MidiKey key, QVariant data)
{
    Q_UNUSED(channel);
    if (key.type() == MidiKey::PitchBend) {
        outputPort("Pitch")->send(data.value<double>());
    }
}
