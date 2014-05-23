#include "nordstage2controlout.h"
#include "../inputport.h"
#include "Settings/selectsetting.h"
#include "Settings/midicommandselectsetting.h"
#include <QDebug>
#include "nordstage2.h"

REGISTER_DEFN_NODETYPE(NordStage2ControlOut);


NordStage2ControlOut::NordStage2ControlOut(QPoint position, Project *parent) :
    MidiChannelNode(position, parent, "NordStage2 Control Out")
{
    _inputs += new InputPort(this, "trigger", "set the specified value", Port::Trigger);
    _inputs += new InputPort(this, "category", "category", Port::Scalar);
    _inputs += new InputPort(this, "property", "property", Port::Scalar);
    _inputs += new InputPort(this, "data", "set the data", Port::Scalar);

    _midiSetting = new MidiCommandSelectSetting(this, "Midi Command", "Sets the midi command that is fired when the trigger input is triggered");

    connect(_midiSetting, SIGNAL(sendMidi()), this, SLOT(sendMidi()));

    connect(_inputs[1], SIGNAL(receivedData(QVariant)), this, SLOT(sendMidi()));

    connect(_inputs[2], &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert(QVariant::Int)) return;
        _midiSetting->setChannel(data.value<int>());
    });
    connect(_inputs[3], &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert(QVariant::Int)) return;
        _midiSetting->setCategoryIndex(data.value<int>());
    });
    connect(_inputs[4], &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert(QVariant::Int)) return;
        _midiSetting->setPropertyIndex(data.value<int>());
    });

    connect(_inputs[4], &InputPort::receivedData, [this](QVariant data) {
        switch (_midiSetting->domainType()) {
        case Domain::Discrete:
            if (data.canConvert(QVariant::Int))
                _midiSetting->setIndex(data.value<int>());
            break;
        case Domain::Integer:
            if (data.canConvert(QVariant::Int)) {
                _midiSetting->setInt(data.value<int>());
            }
            break;
        case Domain::Double:
            if (data.canConvert(QVariant::Double))
                _midiSetting->setDouble(data.value<double>());
            break;
        }
    });
}

void NordStage2ControlOut::sendMidi()
{
    NordStage2::channel(_midiSetting->channel())->
            sendMidiCommand(
                _midiSetting->domain()->midiKey(),
                _midiSetting->domain()->encode()
                );
}

