#include "nordstage2noteout.h"
#include "../inputport.h"
#include "nordstage2.h"

REGISTER_DEFN_NODETYPE(NordStage2NoteOut);

NordStage2NoteOut::NordStage2NoteOut(QPoint position, Project* parent) :
    MidiChannelNode(position, parent, "NordStage2 Note Out")
{
    _inputs += new InputPort(this, "Note on", "", Port::Trigger);
    _inputs += new InputPort(this, "Note off", "", Port::Trigger);
    _inputs += new InputPort(this, "Note", "", Port::Scalar);
    _inputs += new InputPort(this, "Velocity", "", Port::Scalar);

    _note = new IntegerSetting(this, "Note", "", 0, 127, 60, 1, 60);
    _velocity = new IntegerSetting(this, "Velocity", "", 0, 127, 127, 1, 127);

    connect(_inputs[1], &InputPort::receivedData, [this](){
        sendNoteOn(_note->value(), _velocity->value());
    });

    connect(_inputs[2], &InputPort::receivedData, [this](){
        sendNoteOff(_note->value(), _velocity->value());
    });

    _note->connectPort(_inputs[3]);
    _velocity->connectPort(_inputs[4]);

}

void NordStage2NoteOut::sendNoteOff(quint8 note, quint8 velocity)
{
    MidiKey key(MidiKey::NoteOff, note);
    NordStage2::channel(channel())->sendMidiCommand(key, velocity);
}

void NordStage2NoteOut::sendNoteOn(quint8 note, quint8 velocity)
{
    MidiKey key(MidiKey::NoteOn, note);
    NordStage2::channel(channel())->sendMidiCommand(key, velocity);
}
