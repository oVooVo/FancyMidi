#ifndef RANGENODE_H
#define RANGENODE_H

#include "node.h"

class RangeNode : public Node
{
    Q_OBJECT
public:
    RangeNode(QDataStream& stream);

    QString category() const { return "Math"; }

    REGISTER_DECL_NODETYPE(RangeNode);
};

#endif // RANGENODE_H
