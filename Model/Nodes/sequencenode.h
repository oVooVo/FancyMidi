#ifndef SEQUENCENODE_H
#define SEQUENCENODE_H

#include "node.h"

class SequenceNode : public Node
{
    Q_OBJECT
public:
    SequenceNode(QDataStream& stream);

    REGISTER_DECL_NODETYPE(SequenceNode);
};

#endif // SEQUENCENODE_H
