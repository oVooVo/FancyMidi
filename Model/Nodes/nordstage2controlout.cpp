#include "nordstage2controlout.h"
#include "../inputport.h"
#include "Settings/selectsetting.h"
#include "Settings/midicommandselectsetting.h"
#include <QDebug>
#include "nordstage2.h"
#include "../datainputport.h"

REGISTER_DEFN_NODETYPE(NordStage2ControlOut);

NordStage2ControlOut::NordStage2ControlOut(QDataStream& stream) :
    Node(stream)
{
    setName("Control Out");
    addPort(new TriggerInputPort(this, "Trigger", ""));
    addPort(new DataInputPort(this, "Channel", ""));
    addPort(new DataInputPort(this, "Category", ""));
    addPort(new DataInputPort(this, "Property", ""));
    addPort(new DataInputPort(this, "Data", ""));


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
    } else {
        Q_ASSERT(false);
    }
}

