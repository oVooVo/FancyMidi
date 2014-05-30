#include "nordstage2noteout.h"
#include "../inputport.h"
#include "nordstage2.h"
#include <QTimer>

REGISTER_DEFN_NODETYPE(NordStage2NoteOut);

NordStage2NoteOut::NordStage2NoteOut(QDataStream &stream)
    : Node(stream)
{
}

void NordStage2NoteOut::sendNoteOff(quint8 note, quint8 velocity)
{
}

void NordStage2NoteOut::sendNoteOn(quint8 note, quint8 velocity)
{
}


