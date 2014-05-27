#include "pitchbendoutput.h"
#include "Settings/doublesetting.h"
#include "nordstage2.h"

REGISTER_DEFN_NODETYPE(PitchBendOutput);

PitchBendOutput::PitchBendOutput(QDataStream& stream) : MidiChannelNode(stream)
{
    setName("Pitch Bend Output");
    addPort(new InputPort(this, "Pitch", "", Port::Scalar));
    addPort(new InputPort(this, "Trigger", "", Port::Trigger));
    addSetting(new DoubleSetting(this, "Pitch", "", -2, 2, 0, 0));
    setting<DoubleSetting>("Pitch")->connectPort(inputPort("Pitch"));

    connect(inputPort("Trigger"), &InputPort::receivedData, [this]() {
        QPair<MidiKey, quint8> code = Domains::encodePitch(setting<DoubleSetting>("Pitch")->value());
        NordStage2::channel(channel())->sendMidiCommand(code.first, code.second);
    });
}
