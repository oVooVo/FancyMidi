#ifndef CONDITIONNODE_H
#define CONDITIONNODE_H

#include "node.h"

class ConditionNode : public Node
{
    Q_OBJECT
public:
    ConditionNode(QDataStream& stream);

    QString category() const { return "Logic"; }

    REGISTER_DECL_NODETYPE(ConditionNode);
};

#endif // CONDITIONNODE_H
