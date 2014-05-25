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
    addPort(new InputPort(this, "Trigger", "set the specified value", Port::Trigger));
    addPort(new InputPort(this, "Category", "category", Port::Scalar));
    addPort(new InputPort(this, "Property", "property", Port::Scalar));
    addPort(new InputPort(this, "Data", "set the data", Port::Scalar));

    addSetting(new MidiCommandSelectSetting(this, "Midi Command", "Sets the midi command that is fired when the trigger input is triggered"));

    connect(setting<MidiCommandSelectSetting>("Midi Command"), SIGNAL(sendMidi()), this, SLOT(sendMidi()));

    connect(inputPort("Trigger"), SIGNAL(receivedData(QVariant)), this, SLOT(sendMidi()));


    connect(inputPort("Category"), &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert(QVariant::Int)) return;
        setting<MidiCommandSelectSetting>("Midi Command")->setCategoryIndex(data.value<int>());
    });
    connect(inputPort("Property"), &InputPort::receivedData, [this](QVariant data) {
        if (!data.canConvert(QVariant::Int)) return;
        setting<MidiCommandSelectSetting>("Midi Command")->setPropertyIndex(data.value<int>());
    });

    connect(inputPort("Data"), &InputPort::receivedData, [this](QVariant data) {
        switch (setting<MidiCommandSelectSetting>("Midi Command")->domainType()) {
        case Domain::Discrete:
            if (data.canConvert(QVariant::Int))
                setting<MidiCommandSelectSetting>("Midi Command")->setIndex(data.value<int>());
            break;
        case Domain::Integer:
            if (data.canConvert(QVariant::Int)) {
                setting<MidiCommandSelectSetting>("Midi Command")->setInt(data.value<int>());
            }
            break;
        case Domain::Double:
            if (data.canConvert(QVariant::Double))
                setting<MidiCommandSelectSetting>("Midi Command")->setDouble(data.value<double>());
            break;
        }
    });
}

void NordStage2ControlOut::sendMidi()
{
    NordStage2::channel(setting<MidiCommandSelectSetting>("Midi Command")->channel())->
            sendMidiCommand(
                setting<MidiCommandSelectSetting>("Midi Command")->domain()->midiKey(),
                setting<MidiCommandSelectSetting>("Midi Command")->domain()->encode()
                );
}

