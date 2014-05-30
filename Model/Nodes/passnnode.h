#ifndef PASSNNODE_H
#define PASSNNODE_H

#include "node.h"

class PassNNode : public Node
{
    Q_OBJECT

public:
    PassNNode(QDataStream& stream);

    QString category() const { return "Logic"; }



private:
    int _i = 0;
    REGISTER_DECL_NODETYPE(PassNNode);
};

#endif // PASSNNODE_H
