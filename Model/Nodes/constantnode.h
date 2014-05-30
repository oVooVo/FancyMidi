#ifndef CONSTANTNODE_H
#define CONSTANTNODE_H

#include "node.h"
#include "../dataoutputport.h"


class ConstantNode : public Node
{
    Q_OBJECT
public:
    ConstantNode(QDataStream& stream);

    QString category() const { return "General"; }

    REGISTER_DECL_NODETYPE(ConstantNode);
};

#endif // CONSTANTNODE_H
