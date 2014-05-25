#ifndef NORDSTAGE2NODE_H
#define NORDSTAGE2NODE_H

#include "../Nodes/midichannelnode.h"
#include "Settings/integersetting.h"
#include "Settings/midicommandselectsetting.h"

class NordStage2ControlOut : public MidiChannelNode
{
    Q_OBJECT
public:
    NordStage2ControlOut(QDataStream& stream);
    QString category() const { return "Midi Out"; }

private:
    REGISTER_DECL_NODETYPE(NordStage2ControlOut);


public slots:
    void sendMidi();


};

#endif // NORDSTAGE2NODE_H
