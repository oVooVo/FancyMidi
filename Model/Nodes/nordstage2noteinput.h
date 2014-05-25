#ifndef NORDSTAGE2NOTEINPUT_H
#define NORDSTAGE2NOTEINPUT_H

#include "midichannelnode.h"
#include "midikey.h"

class NordStage2NoteInput : public MidiChannelNode
{
    Q_OBJECT
public:
    NordStage2NoteInput(QPoint position, Project* parent);
    REGISTER_DECL_NODETYPE(NordStage2NoteInput);

    QString category() const { return "Input"; }

private slots:
    void receiveMidiCommand(int channel, MidiKey key, QVariant data);
};

#endif // NORDSTAGE2NOTEINPUT_H
