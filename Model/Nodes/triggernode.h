#ifndef TRIGGERNODE_H
#define TRIGGERNODE_H

#include "node.h"

class TriggerNode : public Node
{
    Q_OBJECT
public:
    TriggerNode(QDataStream& stream);

    QString category() const { return "General"; }

    REGISTER_DECL_NODETYPE(TriggerNode);
};

#endif // TRIGGERNODE_H
