#ifndef NORDSTAGE2NOTEOUT_H
#define NORDSTAGE2NOTEOUT_H

#include "../Nodes/midichannelnode.h"
#include "Settings/integersetting.h"
#include "Settings/doublesetting.h"

class NordStage2NoteOut : public MidiChannelNode
{
    Q_OBJECT
public:
    NordStage2NoteOut(QPoint position, Project *parent);
    QString category() const { return "Midi Out"; }



private:
    IntegerSetting* _note;
    IntegerSetting* _velocity;
    REGISTER_DECL_NODETYPE(NordStage2NoteOut);

public slots:
    void sendNoteOn(quint8 note, quint8 velocity);
    void sendNoteOff(quint8 note, quint8 velocity);
};

#endif // NORDSTAGE2NOTEOUT_H
