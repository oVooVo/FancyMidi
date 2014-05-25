#include "nordstage2noteout.h"
#include "../inputport.h"
#include "nordstage2.h"

REGISTER_DEFN_NODETYPE(NordStage2NoteOut);

NordStage2NoteOut::NordStage2NoteOut(QDataStream &stream)
    : MidiChannelNode(stream)
{
    setName("Note Out");
    addPort(new InputPort(this, "Note on", "", Port::Trigger));
    addPort(new InputPort(this, "Note off", "", Port::Trigger));
    addPort(new InputPort(this, "Note", "", Port::Scalar));
    addPort(new InputPort(this, "Velocity", "", Port::Scalar));

    addSetting(new IntegerSetting(this, "Note", "", 0, 127, 60, 60));
    addSetting(new IntegerSetting(this, "Velocity", "", 0, 127, 127, 127));

    connect(inputPort("Note on"), &InputPort::receivedData, [this](){
        sendNoteOn(setting<IntegerSetting>("Note")->value(), setting<IntegerSetting>("Velocity")->value());
    });

    connect(inputPort("Note off"), &InputPort::receivedData, [this](){
        sendNoteOff(setting<IntegerSetting>("Note")->value(), setting<IntegerSetting>("Velocity")->value());
    });

    setting<IntegerSetting>("Note")->connectPort(inputPort("Note"));
    setting<IntegerSetting>("Velocity")->connectPort(inputPort("Velocity"));
}

void NordStage2NoteOut::sendNoteOff(quint8 note, quint8 velocity)
{
    if (!block()) {
        MidiKey key(MidiKey::NoteOff, note);
        NordStage2::channel(channel())->sendMidiCommand(key, velocity);
    }
}

void NordStage2NoteOut::sendNoteOn(quint8 note, quint8 velocity)
{
    if (!block()) {
        MidiKey key(MidiKey::NoteOn, note);
        NordStage2::channel(channel())->sendMidiCommand(key, velocity);
    }
}


