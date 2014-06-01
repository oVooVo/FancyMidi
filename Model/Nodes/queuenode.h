#ifndef QUEUENODE_H
#define QUEUENODE_H

#include "node.h"
#include "../datainputport.h"
#include "../triggerinputport.h"

class QueueNode : public Node
{
    Q_OBJECT
public:
    QueueNode(QDataStream& stream);

    QString category() const { return "Memory"; }

    void trigger(const TriggerInputPort *in);

private:
    QVariant _datum;

    REGISTER_DECL_NODETYPE(QueueNode);
};

#endif // QUEUENODE_H
