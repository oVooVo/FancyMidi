#ifndef PITCHBENDINPUT_H
#define PITCHBENDINPUT_H

#include "midichannelnode.h"
#include "midikey.h"


class PitchBendInput : public MidiChannelNode
{
    Q_OBJECT
public:
    PitchBendInput(QDataStream& stream);
    QString category() const { return "Midi"; }

    void notify(const DataInputPort *in, const QVariant &data);

private slots:
    void filter(int channel, MidiKey key, QVariant data);

private:
    int _connectedChannel;

    REGISTER_DECL_NODETYPE(PitchBendInput);
};

#endif // PITCHBENDINPUT_H
