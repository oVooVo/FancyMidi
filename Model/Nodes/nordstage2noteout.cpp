#include "nordstage2noteout.h"
#include "../inputport.h"
#include "nordstage2.h"
#include <QTimer>
#include "../datainputport.h"

REGISTER_DEFN_NODETYPE(NordStage2NoteOut);

NordStage2NoteOut::NordStage2NoteOut(QDataStream &stream)
    : MidiChannelNode(stream)
{
    addPort(new TriggerInputPort(this, "Note on", ""));
    addPort(new TriggerInputPort(this, "Note off", ""));
    addPort(new DataInputPort(this, "Note", "", false));
    addPort(new DataInputPort(this, "Velocity", "", false));

    addSetting(new IntegerSetting(this, "Note",     "", 0, 127, 60, 60));
    addSetting(new IntegerSetting(this, "Velocity", "", 0, 127, 60, 60));

    setting<IntegerSetting>("Note")->connectPort(dataInputPort("Note"));
    setting<IntegerSetting>("Velocity")->connectPort(dataInputPort("Velocity"));

}

void NordStage2NoteOut::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Note on")) {
        sendNoteOn (dataInputPort("Note")->data().value<int>(),
                    dataInputPort("Velocity")->data().value<int>());
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
    /*
    if (_timers.contains(note))
        delete _timers.take(note);

    if (setting<BoolSetting>("Use Delay")->value()) {
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [timer, note, velocity, this](){
            _timers.remove(note);
            delete timer;
            sendNoteOff(note, velocity);
        });
        _timers.insert(note, timer);
        timer->setSingleShot(true);
        timer->start(setting<IntegerSetting>("Delay")->value());
    }
    */

    MidiKey key(MidiKey::NoteOn, note);
    NordStage2::channel(channel())->sendMidiCommand(key, velocity);
}

