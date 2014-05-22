#include "nordstage2node.h"
#include "../simpleinputport.h"
#include "Settings/selectsetting.h"
#include "Settings/midicommandselectsetting.h"
#include <QDebug>
#include "nordstage2.h"


NordStage2Node::NordStage2Node(QPoint position, Project *parent) :
    Node(position, parent, "NordStage2")
{
    _inputs += new SimpleInputPort(this, "", "set the specified value");

    _midiSetting = new MidiCommandSelectSetting(this, "Midi Command", "Sets the midi command that is fired when the trigger input is triggered");
    _intSetting = new IntegerSetting(this, "Channel", "Midi channel", 0, 15, 0, 1, 0);
    connect(_intSetting, &IntegerSetting::changed, [this]() {
        emit channelChanged(_intSetting->value());
    });
    connect(_midiSetting, SIGNAL(sendMidi()), this, SLOT(sendMidi()));

    polish();
}

void NordStage2Node::sendMidi()
{
    NordStage2::channel(channel())->sendMidiControlCommand(_midiSetting->domain()->midicode(), _midiSetting->domain()->encode());
}
