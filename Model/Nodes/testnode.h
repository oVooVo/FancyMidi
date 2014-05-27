#ifndef TESTNODE_H
#define TESTNODE_H

#include "node.h"

class TestNode : public Node
{
    Q_OBJECT
public:
    TestNode(QDataStream& stream);

    REGISTER_DECL_NODETYPE(TestNode);
};

#endif // TESTNODE_H
