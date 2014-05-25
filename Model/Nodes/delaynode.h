#ifndef DELAYNODE_H
#define DELAYNODE_H

#include "enableablenode.h"
#include "Settings/integersetting.h"

class DelayNode : public EnableableNode
{
    Q_OBJECT
public:
    DelayNode(QPoint point, Project* parent);

    REGISTER_DECL_NODETYPE(DelayNode);
};

#endif // DELAYNODE_H
