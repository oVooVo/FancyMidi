#include "nordstage2input.h"
#include "../outputport.h"
#include "nordstage2.h"

REGISTER_DEFN_NODETYPE(NordStage2Input);

NordStage2Input::NordStage2Input(QPoint position, Project* parent)
    : Node(position, parent, "NordStage2 input", "midi input filter")
{
    _outputs += new OutputPort(this, "trigger", "", Port::Trigger);
    _outputs += new OutputPort(this, "channel", "", Port::Scalar);
    _outputs += new OutputPort(this, "category", "", Port::Scalar);
    _outputs += new OutputPort(this, "property", "", Port::Scalar);
    _outputs += new OutputPort(this, "value", "", Port::Scalar);

    _midiFilter = new MidiFilterSetting(this, "Midi Filter", "");

    for (int i = 0; i < 15; i++) {
        connect(NordStage2::channel(i), SIGNAL(midiInput(int,MidiKey,QVariant)),
                this, SLOT(filter(int,MidiKey,QVariant)));
    }
}

void NordStage2Input::filter(int channel, MidiKey key, QVariant data)
{
    if (_midiFilter->filterChannel()
            &&    channel != _midiFilter->channel()) return;
    if (_midiFilter->filterType()
            && key.type() != _midiFilter->type()) return;
    if (_midiFilter->filterCategory()
            && NordStage2::categoryIndex(key) != _midiFilter->categoryIndex()) return;
    if (_midiFilter->filterProperty()
            && NordStage2::propertyIndex(key) != _midiFilter->propertyIndex()) return;

    int categoryIndex = NordStage2::categoryIndex(key);
    int propertyIndex = NordStage2::propertyIndex(key);
    _outputs[0]->send();
    _outputs[1]->send(channel);
    if (key.type() == MidiKey::ControlChange) {
        _outputs[2]->send(NordStage2::categories()[categoryIndex]);
        _outputs[3]->send(NordStage2::properties(categoryIndex)[propertyIndex]);
    }
    _outputs[4]->send(data);

}
