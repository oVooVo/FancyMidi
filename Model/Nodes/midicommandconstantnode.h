#ifndef MIDICOMMANDCONSTANTNODE_H
#define MIDICOMMANDCONSTANTNODE_H

#include "node.h"
#include "../dataoutputport.h"
#include "../triggeroutputport.h"

class MidiCommandConstantNode : public Node
{
    Q_OBJECT
public:

    MidiCommandConstantNode(QDataStream& stream);
    QString category() const { return "Midi"; }
    void updateData(const DataOutputPort *) const;

    REGISTER_DECL_NODETYPE(MidiCommandConstantNode);
};

#endif // MIDICOMMANDCONSTANTNODE_H
