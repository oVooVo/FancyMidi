#include "nordstage2input.h"
#include "../outputport.h"
#include "nordstage2.h"
#include "../datainputport.h"
#include "../dataoutputport.h"
#include "../triggeroutputport.h"

REGISTER_DEFN_NODETYPE(NordStage2Input);

NordStage2Input::NordStage2Input(QDataStream& stream)
    : Node(stream)
{
    setName("Control Input");
    addPort(new DataOutputPort(this, "Channel", ""));
    addPort(new DataOutputPort(this, "Category", ""));
    addPort(new DataOutputPort(this, "Property", ""));
    addPort(new DataOutputPort(this, "Type", ""));
    addPort(new DataOutputPort(this, "Value", ""));
    addPort(new TriggerOutputPort(this, "Trigger", ""));

    addSetting(new MidiFilterSetting(this, "Midi Filter", ""));

    connect(setting<MidiFilterSetting>("Midi Filter"), &MidiFilterSetting::channelChanged, [this](int channel) {
        dataOutputPort("Channel")->setData(channel);
    });
    connect(setting<MidiFilterSetting>("Midi Filter"), &MidiFilterSetting::categoryChanged, [this](int category) {
        dataOutputPort("Category")->setData(category);
    });
    connect(setting<MidiFilterSetting>("Midi Filter"), &MidiFilterSetting::propertyChanged, [this](int property) {
        dataOutputPort("Property")->setData(property);
    });
    connect(setting<MidiFilterSetting>("Midi Filter"), &MidiFilterSetting::typeChanged, [this](int type) {
        dataOutputPort("Type")->setData(type);
    });

    for (int i = 0; i < Keyboard::NUM_MIDI_CHANNELS; i++) {
        connect(NordStage2::channel(i), SIGNAL(midiInput(int,MidiKey,QVariant)),
                this, SLOT(filter(int,MidiKey,QVariant)));
    }
}

void NordStage2Input::filter(int channel, MidiKey key, QVariant data)
{
    if (setting<MidiFilterSetting>("Midi Filter")->filterChannel()
            &&    channel != setting<MidiFilterSetting>("Midi Filter")->channel()) {
        return;
    }
    if (setting<MidiFilterSetting>("Midi Filter")->filterType()
            && key.type() != setting<MidiFilterSetting>("Midi Filter")->type())  {
        return;
    }
    if (setting<MidiFilterSetting>("Midi Filter")->filterCategory()
            && setting<MidiFilterSetting>("Midi Filter")->type() == MidiKey::ControlChange
            && NordStage2::categoryIndex(key) != setting<MidiFilterSetting>("Midi Filter")->categoryIndex()) {
        return;
    }
    if (setting<MidiFilterSetting>("Midi Filter")->filterProperty()
            && setting<MidiFilterSetting>("Midi Filter")->type() == MidiKey::ControlChange
            && NordStage2::propertyIndex(key) != setting<MidiFilterSetting>("Midi Filter")->propertyIndex()) {
        return;
    }
    int categoryIndex = NordStage2::categoryIndex(key);
    int propertyIndex = NordStage2::propertyIndex(key);
    dataOutputPort("Channel")->setData(channel);
    if (key.type() == MidiKey::ControlChange) {
        dataOutputPort("Category")->setData(NordStage2::categories()[categoryIndex]);
        dataOutputPort("Property")->setData(NordStage2::properties(categoryIndex)[propertyIndex]);
    }
    if (key.type() == MidiKey::Aftertouch) {
        dataOutputPort("Value")->setData(key.code() / 127.0);  // map aftertouch from 0..127 to 0..1
    } else {
        dataOutputPort("Value")->setData(data);
    }
    triggerOutputPort("Trigger")->trigger();
}
