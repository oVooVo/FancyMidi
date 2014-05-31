#ifndef PITCHBENDOUTPUT_H
#define PITCHBENDOUTPUT_H

#include "midichannelnode.h"
#include "../triggerinputport.h"

class PitchBendOutput : public MidiChannelNode
{
    Q_OBJECT
public:
    PitchBendOutput(QDataStream &stream);

    QString category() const { return "Midi"; }

    void trigger(const TriggerInputPort *in);

    REGISTER_DECL_NODETYPE(PitchBendOutput);
};

#endif // PITCHBENDOUTPUT_H
