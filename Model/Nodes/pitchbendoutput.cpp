#include "pitchbendoutput.h"
#include "Settings/doublesetting.h"
#include "nordstage2.h"
#include "../datainputport.h"

REGISTER_DEFN_NODETYPE(PitchBendOutput);

PitchBendOutput::PitchBendOutput(QDataStream& stream) : MidiChannelNode(stream)
{
    setName("Pitch Bend Output");
    addPort(new DataInputPort(this, "Pitch", ""));
    addPort(new TriggerInputPort(this, "Trigger", ""));

    addSetting(new DoubleSetting(this, "Pitch", "", -2, 2, 0, 0));
    setting<DoubleSetting>("Pitch")->connectPort(dataInputPort("Pitch"));
}

void PitchBendOutput::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Trigger")) {
        QPair<MidiKey, quint8> code = Domains::encodePitch(dataInputPort("Pitch")->data().value<double>());
        NordStage2::channel(channel())->sendMidiCommand(code.first, code.second);
    } else {
        UNKNOWN_PORT;
    }
}
