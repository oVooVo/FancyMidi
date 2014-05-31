#include "nordstage2noteout.h"
#include "../inputport.h"
#include "nordstage2.h"
#include <QTimer>
#include "../datainputport.h"

REGISTER_DEFN_NODETYPE(NordStage2NoteOut);

NordStage2NoteOut::NordStage2NoteOut(QDataStream &stream)
    : MidiChannelNode(stream)
{
    setName("Note Output");
    addPort(new TriggerInputPort(this, "Note on", ""));
    addPort(new TriggerInputPort(this, "Note off", ""));
    addPort(new DataInputPort(this, "Note", "", false));
    addPort(new DataInputPort(this, "Velocity", "", false));

    addSetting(new IntegerSetting(this, "Note",     "", 0, 127, 60, 60));
    addSetting(new DoubleSetting(this, "Velocity", "", 0, 1, 1, 1));

    setting<IntegerSetting>("Note")->connectPort(dataInputPort("Note"));
    setting<DoubleSetting>("Velocity")->connectPort(dataInputPort("Velocity"));

}

void NordStage2NoteOut::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Note on")) {
        sendNoteOn (dataInputPort("Note")->data().value<double>(),
                    dataInputPort("Velocity")->data().value<double>() * 127);
    } else if (in == triggerInputPort("Note off")) {
        sendNoteOff(dataInputPort("Note")->data().value<int>(),
                    dataInputPort("Velocity")->data().value<int>());
    }
}

void NordStage2NoteOut::sendNoteOff(quint8 note, quint8 velocity)
{
    if (_timers.contains(note))
        delete _timers.take(note);

    MidiKey key(MidiKey::NoteOff, note);
    NordStage2::channel(channel())->sendMidiCommand(key, velocity);
}

void NordStage2NoteOut::sendNoteOn(quint8 note, quint8 velocity)
{
    MidiKey key(MidiKey::NoteOn, note);
    NordStage2::channel(channel())->sendMidiCommand(key, velocity);
}

