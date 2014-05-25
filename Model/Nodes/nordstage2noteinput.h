#ifndef NORDSTAGE2NOTEINPUT_H
#define NORDSTAGE2NOTEINPUT_H

#include "midichannelnode.h"
#include "midikey.h"

class NordStage2NoteInput : public MidiChannelNode
{
    Q_OBJECT
public:
    NordStage2NoteInput(QDataStream& stream);


    QString category() const { return "Input"; }

private slots:
    void receiveMidiCommand(int channel, MidiKey key, QVariant data);
    REGISTER_DECL_NODETYPE(NordStage2NoteInput);
};

#endif // NORDSTAGE2NOTEINPUT_H
