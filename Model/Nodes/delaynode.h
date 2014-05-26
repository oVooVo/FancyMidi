#ifndef DELAYNODE_H
#define DELAYNODE_H

#include "enableablenode.h"
#include "Settings/integersetting.h"

class DelayNode : public EnableableNode
{
    Q_OBJECT
public:
    DelayNode(QDataStream& stream);

    QString category() const { return "Time"; }

    REGISTER_DECL_NODETYPE(DelayNode);
};

#endif // DELAYNODE_H
