#include "nordstage2controlout.h"
#include "../inputport.h"
#include "Settings/selectsetting.h"
#include "Settings/midicommandselectsetting.h"
#include <QDebug>
#include "nordstage2.h"
#include "../datainputport.h"

REGISTER_DEFN_NODETYPE(NordStage2ControlOut);

NordStage2ControlOut::NordStage2ControlOut(QDataStream& stream) :
    MidiChannelNode(stream)
{
    setName("Control Output");
    addPort(new TriggerInputPort(this, "Trigger", ""));
    addPort(new DataInputPort(this, "Category", "", false));
    addPort(new DataInputPort(this, "Property", "", false));
    addPort(new DataInputPort(this, "Data", "", false));

    addSetting(new MidiCommandSelectSetting(this, "Midi Command", "", true));
    setting<MidiCommandSelectSetting>("Midi Command")->connectPort(dataInputPort("Category"),
                                                                   dataInputPort("Property"),
                                                                   dataInputPort("Data"));

}

void NordStage2ControlOut::trigger(const TriggerInputPort *in)
{
    if (in == triggerInputPort("Trigger")) {
        MidiCommandSelectSetting mcss(this, "", "", false);
        mcss.setCategoryIndex(dataInputPort("Category")->data().value<int>());
        mcss.setPropertyIndex(dataInputPort("Property")->data().value<int>());
        mcss.setValue(dataInputPort("Data")->data());
        NordStage2::channel(dataInputPort("Channel")->data().value<int>())->
                sendMidiCommand(
                    mcss.domain()->midiKey(),
                    mcss.domain()->encode()
                    );
    }
}

