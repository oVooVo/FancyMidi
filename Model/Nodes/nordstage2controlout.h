#ifndef NORDSTAGE2NODE_H
#define NORDSTAGE2NODE_H

#include "../Nodes/midichannelnode.h"
#include "Settings/integersetting.h"
#include "Settings/midicommandselectsetting.h"
#include "../triggerinputport.h"


class NordStage2ControlOut : public Node    //TODO derive from midichannelnode
{
    Q_OBJECT
public:
    NordStage2ControlOut(QDataStream& stream);
    QString category() const { return "Midi"; }
    void trigger(const TriggerInputPort *);

private:
    REGISTER_DECL_NODETYPE(NordStage2ControlOut);


};

#endif // NORDSTAGE2NODE_H
