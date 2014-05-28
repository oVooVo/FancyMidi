#include "nordstage2input.h"
#include "../outputport.h"
#include "nordstage2.h"

REGISTER_DEFN_NODETYPE(NordStage2Input);

NordStage2Input::NordStage2Input(QDataStream& stream)
    : EnableableNode(stream)
{
    setName("Control Input");
    addPort(new OutputPort(this, "Channel", "", Port::Scalar));
    addPort(new OutputPort(this, "Category", "", Port::Scalar));
    addPort(new OutputPort(this, "Property", "", Port::Scalar));
    addPort(new OutputPort(this, "Type", "", Port::Scalar));
    addPort(new OutputPort(this, "Value", "", Port::Scalar));

    addSetting(new MidiFilterSetting(this, "Midi Filter", ""));

    connect(setting<MidiFilterSetting>("Midi Filter"), &MidiFilterSetting::channelChanged, [this](int channel) {
        outputPort("Channel")->sendData(channel);
    });
    connect(setting<MidiFilterSetting>("Midi Filter"), &MidiFilterSetting::categoryChanged, [this](int category) {
        outputPort("Category")->sendData(category);
    });
    connect(setting<MidiFilterSetting>("Midi Filter"), &MidiFilterSetting::propertyChanged, [this](int property) {
        outputPort("Property")->sendData(property);
    });
    connect(setting<MidiFilterSetting>("Midi Filter"), &MidiFilterSetting::typeChanged, [this](int type) {
        outputPort("Type")->sendData(type);
    });

    for (int i = 0; i < Keyboard::NUM_MIDI_CHANNELS; i++) {
        connect(NordStage2::channel(i), SIGNAL(midiInput(int,MidiKey,QVariant)),
                this, SLOT(filter(int,MidiKey,QVariant)));
    }
}

void NordStage2Input::filter(int channel, MidiKey key, QVariant data)
{
    if (setting<MidiFilterSetting>("Midi Filter")->filterChannel()
            &&    channel != setting<MidiFilterSetting>("Midi Filter")->channel()) return;
    if (setting<MidiFilterSetting>("Midi Filter")->filterType()
            && key.type() != setting<MidiFilterSetting>("Midi Filter")->type()) return;
    if (setting<MidiFilterSetting>("Midi Filter")->filterCategory()
            && setting<MidiFilterSetting>("Midi Filter")->type() == MidiKey::ControlChange
            && NordStage2::categoryIndex(key) != setting<MidiFilterSetting>("Midi Filter")->categoryIndex()) return;
    if (setting<MidiFilterSetting>("Midi Filter")->filterProperty()
            && setting<MidiFilterSetting>("Midi Filter")->type() == MidiKey::ControlChange
            && NordStage2::propertyIndex(key) != setting<MidiFilterSetting>("Midi Filter")->propertyIndex()) return;

    int categoryIndex = NordStage2::categoryIndex(key);
    int propertyIndex = NordStage2::propertyIndex(key);
    outputPort("Channel")->send(channel);
    if (key.type() == MidiKey::ControlChange) {
        outputPort("Category")->send(NordStage2::categories()[categoryIndex]);
        outputPort("Property")->send(NordStage2::properties(categoryIndex)[propertyIndex]);
    }
    outputPort("Value")->send(data);
}
