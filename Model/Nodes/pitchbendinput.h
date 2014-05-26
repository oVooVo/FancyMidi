#ifndef PITCHBENDINPUT_H
#define PITCHBENDINPUT_H

#include "enableablenode.h"
#include "midikey.h"

class PitchBendInput : public EnableableNode
{
    Q_OBJECT
public:
    PitchBendInput(QDataStream& stream);
    QString category() const { return "Midi In"; }

private slots:
    void filter(int channel, MidiKey key, QVariant data);

    REGISTER_DECL_NODETYPE(PitchBendInput);
};

#endif // PITCHBENDINPUT_H
